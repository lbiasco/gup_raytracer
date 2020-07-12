#include "cameras/camera.h"

#include <math.h>

Camera::Camera(Point3D eye, Vector3D view_dir, Vector3D up) 
    : eye_(eye), view_dir_(view_dir), up_(up) {
  ComputeUVW();
}

Camera::Camera(Point3D eye, Point3D lookat, Vector3D up) 
    : eye_(eye), up_(up) {
  LookAt(lookat);
}

void Camera::up(Vector3D v) {
  up_ = v;
  ComputeUVW();
}

void Camera::view_dir(Vector3D v) {
  view_dir_ = v;
  ComputeUVW();
}

void Camera::ComputeUVW() {
	w_ = -Vector3D(view_dir_);
  w_.Normalize();

  // Check for "singularity" (parallel up and w vectors)
  Vector3D up_norm(up_);
  up_norm.Normalize();
  if (std::abs(w_ * up_norm) == 1)
    // Use component-swap/flip hackery to guarantee non-parallel
    u_ = Vector3D(-up_norm.z, up_norm.x, up_norm.y) ^ w();
  else
    u_ = up_ ^ w_;
  
  u_.Normalize();
  v_ = w_ ^ u_;
}

void Camera::LookAt(Point3D lookat) {
  //(TODO) Check for zero length e - l or up
  view_dir_ = lookat - eye_;
  ComputeUVW();
}
