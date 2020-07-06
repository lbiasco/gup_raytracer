#include "cameras/camera.h"

// -------------------------------------------------------------------- default constructor

Camera::Camera(Point3D eye, Point3D lookat, Vector3D up) 
    : eye_(eye), lookat_(lookat), up_(up) {
    ComputeUVW();
}


// -------------------------------------------------------------------- constructor

Camera::Camera(Point3D eye, Point3D lookat) 
    : Camera(eye, lookat, Vector3D(0.0, 1.0, 0.0)) {}


// -------------------------------------------------------------------- destructor

Camera::~Camera(void) {}


// -------------------------------------------------------------------- ComputeUVW

void	
Camera::ComputeUVW(void) {
	w_ = eye_ - lookat_;
    w_.Normalize();
    u_ = up_ ^ w_;
    u_.Normalize();
    v_ = w_ ^ u_;
}
