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
    RotateAbout(u_, rotate_u_);
  if (rotate_v_ != 0)
    RotateAbout(v_, rotate_v_);
  if (rotate_w_ != 0)
    RotateAbout(w_, rotate_w_);
}

void Camera::RotateAbout(Vector3D axis, double degrees) {
  // (TODO) Investigate switching to quaternions
  // Frequent values
  double d = std::sqrt(axis.y * axis.y + axis.z * axis.z);

  // Rotational matrix around x (and inverse)
  Matrix r_x;
  Matrix r_x_inv;
  if (d != 0) {
    double cd = axis.z / d;
    double bd = axis.y / d;
    r_x.m[1][1] = cd; r_x.m[2][2] = cd; r_x.m[1][2] = -bd; r_x.m[2][1] = bd;
    r_x_inv.m[1][1] = cd; r_x_inv.m[2][2] = cd; r_x_inv.m[1][2] = bd; r_x_inv.m[2][1] = -bd;
  }

  // Rotational matrix around y (and inverse)
  Matrix r_y;
  Matrix r_y_inv;
  double a = axis.x;
  r_y.m[0][0] = d; r_y.m[0][2] = -a; r_y.m[2][0] = a; r_y.m[2][2] = d;
  r_y_inv.m[0][0] = d; r_y_inv.m[0][2] = a; r_y_inv.m[2][0] = -a; r_y_inv.m[2][2] = d;

  // Rotation matrix around z (which will be the specified axis)
  Matrix r_z;
  double cos_th = std::cos(degrees * kPiOver180);
  double sin_th = std::sin(degrees * kPiOver180);
  r_z.m[0][0] = cos_th; r_z.m[0][1] = -sin_th; r_z.m[1][0] = sin_th; r_z.m[1][1] = cos_th;

  // Apply rotations: x_inv * y_inv * z * y * x * vector
  Matrix r_matrix = r_x_inv * r_y_inv * r_z * r_y * r_x;
  u_ = r_matrix * u_;
  v_ = r_matrix * v_;
  w_ = r_matrix * w_;
}
