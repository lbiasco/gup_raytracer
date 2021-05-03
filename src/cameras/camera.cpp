#include "cameras/camera.h"

#include <math.h>
#include <tgmath.h>

#include "utilities/constants.h"
#include "utilities/matrix.h"

Camera::Camera(Point3D eye, Vector3D viewDir, Vector3D up) 
    : _eye(eye), _viewDir(viewDir), _up(up) {
}

Camera::Camera(Point3D eye, Point3D lookat, Vector3D up) 
    : _eye(eye), _up(up) {
  LookAt(lookat);
}

Point3D Camera::eye() const {
  return _eye + _translateU * _u + _translateV * _v + _translateW * _w;
}

void Camera::ComputeUVW() {
	_w = -Vector3D(_viewDir);
  _w.Normalize();

  // Check for "singularity" (parallel up and w vectors)
  if ((_up ^ _w) == Vector3D(0, 0, 0))
    // Use component-swap/flip hackery to guarantee non-parallel
    _u = Vector3D(-_up.z, _up.x, _up.y) ^ _w;
  else
    _u = _up ^ _w;
  
  _u.Normalize();
  _v = _w ^ _u;

  TransformUVW();
}

void Camera::LookAt(Point3D lookat) {
  _viewDir = lookat - _eye;
  if (_viewDir == Vector3D(0, 0, 0))
    _viewDir = Vector3D(0, 0, 1);
}

void Camera::TransformUVW() {
  if (_rotateU != 0)
    _v = Vector3D::RotateAbout(_v, _u, _rotateU);
    _w = Vector3D::RotateAbout(_w, _u, _rotateU);
  if (_rotateV != 0)
    _u = Vector3D::RotateAbout(_u, _v, _rotateV);
    _w = Vector3D::RotateAbout(_w, _v, _rotateV);
  if (_rotateW != 0)
    _u = Vector3D::RotateAbout(_u, _w, _rotateW);
    _v = Vector3D::RotateAbout(_v, _w, _rotateW);
}
