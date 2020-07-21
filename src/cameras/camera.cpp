#include "cameras/camera.h"

#include <math.h>
#include <tgmath.h>

#include "utilities/constants.h"
#include "utilities/matrix.h"

Camera::Camera(Point3D eye, Vector3D view_dir, Vector3D up) 
    : eye_(eye), view_dir_(view_dir), up_(up) {
}

Camera::Camera(Point3D eye, Point3D lookat, Vector3D up) 
    : eye_(eye), up_(up) {
  LookAt(lookat);
}

Point3D Camera::eye() const {
  return eye_ + translate_u_ * u_ + translate_v_ * v_ + translate_w_ * w_;
}

void Camera::ComputeUVW() {
	w_ = -Vector3D(view_dir_);
  w_.Normalize();

  // Check for "singularity" (parallel up and w vectors)
  if ((up_ ^ w_) == Vector3D(0, 0, 0))
    // Use component-swap/flip hackery to guarantee non-parallel
    u_ = Vector3D(-up_.z, up_.x, up_.y) ^ w_;
  else
    u_ = up_ ^ w_;
  
  u_.Normalize();
  v_ = w_ ^ u_;

  TransformUVW();
}

void Camera::LookAt(Point3D lookat) {
  view_dir_ = lookat - eye_;
  if (view_dir_ == Vector3D(0, 0, 0))
    view_dir_ = Vector3D(0, 0, 1);
}

void Camera::TransformUVW() {
  if (rotate_u_ != 0)
    v_ = Vector3D::RotateAbout(v_, u_, rotate_u_);
    w_ = Vector3D::RotateAbout(w_, u_, rotate_u_);
  if (rotate_v_ != 0)
    u_ = Vector3D::RotateAbout(u_, v_, rotate_v_);
    w_ = Vector3D::RotateAbout(w_, v_, rotate_v_);
  if (rotate_w_ != 0)
    u_ = Vector3D::RotateAbout(u_, w_, rotate_w_);
    v_ = Vector3D::RotateAbout(v_, w_, rotate_w_);
}
