#include "cameras/camera.h"

#include <math.h>
#include <tgmath.h>

#include "utilities/constants.h"
#include "utilities/matrix.h"

Camera::Camera(Vector3D eye, Vector3D viewDir, Vector3D up) 
    : _eye(eye), _viewDir(viewDir), _up(up) {
}

Vector3D Camera::eye() const {
    return _eye + _translateU * _u + _translateV * _v + _translateW * _w;
}

double Camera::ComputeStereoHalfSeparationFromAngle(double angle, double distance) {
    return distance * std::tan(0.5 * angle * kPiOver180);
}

void Camera::ComputeUVW() {
	_w = -Vector3D(_viewDir);
    _w.Normalize();

    // Check for "singularity" (parallel up and w vectors)
    // Use component-swap/flip hackery to guarantee non-parallel
    if ((_up ^ _w) == Vector3D(0, 0, 0))
        _u = Vector3D(-_up.z, _up.x, _up.y) ^ _w;
    else
        _u = _up ^ _w;
    
    _u.Normalize();
    _v = _w ^ _u;

    TransformUVW();
}

void Camera::LookAt(Vector3D lookat) {
    _viewDir = lookat - _eye;
    if (_viewDir == Vector3D(0, 0, 0))
        _viewDir = Vector3D(0, 0, 1);
}

void Camera::TransformUVW() {
    if (_rotateU != 0) {
        _v = Vector3D::RotateAbout(_v, _u, _rotateU);
        _w = Vector3D::RotateAbout(_w, _u, _rotateU);
    }
    if (_rotateV != 0) {
        _u = Vector3D::RotateAbout(_u, _v, _rotateV);
        _w = Vector3D::RotateAbout(_w, _v, _rotateV);
    }
    if (_rotateW != 0) {
        _u = Vector3D::RotateAbout(_u, _w, _rotateW);
        _v = Vector3D::RotateAbout(_v, _w, _rotateW);
    }
}
