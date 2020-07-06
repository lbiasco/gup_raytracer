#include <math.h>

#include "cameras/camera.h"

// -------------------------------------------------------------------- default constructor

Camera::Camera(Point3D eye, Point3D lookat, Vector3D up) 
    : eye_(eye), lookat_(lookat), up_(up) {
    // Check for zero length e - l or up
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

    // Make check for "singularity" (parallel up and w vectors)
    Vector3D up_norm(up_);
    up_norm.Normalize();
    if (std::abs(w_ * up_norm) == 1)
        // Use component-swap/flip hackery to guarantee non-parallel
        u_ = Vector3D(-up_norm.z_, up_norm.x_, up_norm.y_) ^ w_;
    else
        u_ = up_ ^ w_;
    
    u_.Normalize();
    v_ = w_ ^ u_;
}
