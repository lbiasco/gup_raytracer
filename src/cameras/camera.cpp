#include "cameras/camera.h"

#include <math.h>

Camera::Camera(Point3D eye, Point3D lookat, Vector3D up) 
    : eye_(eye), lookat_(lookat), up_(up) {
  //(TODO) Check for zero length e - l or up
  ComputeUVW();
}

Camera::~Camera(void) {}

void Camera::ComputeUVW(void) {
	w_ = eye_ - lookat_;
  w_.Normalize();

  // Check for "singularity" (parallel up and w vectors)
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
