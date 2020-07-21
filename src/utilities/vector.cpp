#include "utilities/vector.h"

#include <math.h>
#include <tgmath.h>

#include "utilities/constants.h"
#include "utilities/matrix.h"
#include "utilities/point.h"

// Implementations of struct Vector2D

Vector2D::Vector2D(const Point2D& p) : x(p.x), y(p.y) {}

Vector2D& Vector2D::Vector2D::operator= (const Point2D& rhs) {
  x = rhs.x; y = rhs.y;
  return *this;
}

Vector2D Vector2D::Hat() const {
  Vector2D copy(*this);
  copy.Normalize();
  return copy;
}


// Implementations of struct Vector3D

Vector3D::Vector3D(const Point3D& p) : x(p.x), y(p.y), z(p.z) {}

Vector3D& Vector3D::Vector3D::operator= (const Point3D& rhs) {
  x = rhs.x; y = rhs.y;  z = rhs.z;
  return *this;
}

Vector3D Vector3D::Hat() const {
  Vector3D copy(*this);
  copy.Normalize();
  return copy;
}

Vector3D Vector3D::RotateAbout(Vector3D v, Vector3D axis, double degrees) {
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
  return r_matrix * v;
}

Vector3D operator* (const Matrix& mat, const Vector3D& v) {
  return (Vector3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
          mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
          mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}
