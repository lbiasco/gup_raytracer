#include "utilities/vector.h"

#include <math.h>

#include "utilities/matrix.h"
#include "utilities/point.h"

// Implementations of struct Vector2D

Vector2D::Vector2D(const Point2D& p) : x(p.x), y(p.y) {}

Vector2D& Vector2D::Vector2D::operator= (const Point2D& rhs) {
  x = rhs.x; y = rhs.y;
  return *this;
}


// Implementations of struct Vector3D

Vector3D::Vector3D(const Point3D& p) : x(p.x), y(p.y), z(p.z) {}

Vector3D& Vector3D::Vector3D::operator= (const Point3D& rhs) {
  x = rhs.x; y = rhs.y;  z = rhs.z;
  return *this;
}

Vector3D operator* (const Matrix& mat, const Vector3D& v) {
  return (Vector3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
          mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
          mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}
