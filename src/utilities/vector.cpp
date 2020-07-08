#include "utilities/vector.h"

#include <math.h>

#include "utilities/normal.h"
#include "utilities/point.h"


// Vector3D

Vector3D::Vector3D(void) : x_(0.0), y_(0.0), z_(0.0) {}

Vector3D::Vector3D(double a) : x_(a), y_(a), z_(a) {}

Vector3D::Vector3D(double x, double y, double z) : x_(x), y_(y), z_(z) {}

Vector3D::Vector3D(const Vector3D& vector) : x_(vector.x_), y_(vector.y_), z_(vector.z_) {}

Vector3D::Vector3D(const Normal& n) : x_(n.x_), y_(n.y_), z_(n.z_) {}

Vector3D::Vector3D(const Point3D& p) : x_(p.x_), y_(p.y_), z_(p.z_) {}

Vector3D::~Vector3D (void) {}

Vector3D& Vector3D::operator= (const Vector3D& rhs) {
  if (this == &rhs)
    return *this;

  x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_;
  return *this;
}

Vector3D& Vector3D::operator= (const Normal& rhs) {
  x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_;
  return *this;
}

Vector3D& Vector3D::operator= (const Point3D& rhs) {
  x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_;
  return *this;
}

double Vector3D::Length(void) {
  return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

void Vector3D::Normalize(void) {	
  double length = sqrt(x_ * x_ + y_ * y_ + z_ * z_);
  x_ /= length; y_ /= length; z_ /= length;
}


// Non-inline, non-member function

Vector3D operator* (const Matrix& mat, const Vector3D& v) {
  return (Point3D(mat.m_[0][0] * v.x_ + mat.m_[0][1] * v.y_ + mat.m_[0][2] * v.z_,
          mat.m_[1][0] * v.x_ + mat.m_[1][1] * v.y_ + mat.m_[1][2] * v.z_,
          mat.m_[2][0] * v.x_ + mat.m_[2][1] * v.y_ + mat.m_[2][2] * v.z_));
}



// Vector3D

Vector2D::Vector2D(void) : x_(0.0), y_(0.0) {}

Vector2D::Vector2D(double a) : x_(a), y_(a) {}

Vector2D::Vector2D(double x, double y) : x_(x), y_(y) {}

Vector2D::Vector2D(const Vector2D& vector) : x_(vector.x_), y_(vector.y_) {}

Vector2D::Vector2D(const Normal& n) : x_(n.x_), y_(n.y_) {}

Vector2D::Vector2D(const Point2D& p) : x_(p.x_), y_(p.y_) {}

Vector2D::~Vector2D (void) {}

Vector2D& Vector2D::operator= (const Vector2D& rhs) {
  if (this == &rhs)
    return *this;

  x_ = rhs.x_; y_ = rhs.y_;
  return *this;
}

Vector2D& Vector2D::operator= (const Normal& rhs) {
  x_ = rhs.x_; y_ = rhs.y_;
  return *this;
}

Vector2D& Vector2D::operator= (const Point2D& rhs) {
  x_ = rhs.x_; y_ = rhs.y_;
  return *this;
}

double Vector2D::Length(void) {
  return sqrt(x_ * x_ + y_ * y_);
}

void Vector2D::Normalize(void) {	
  double length = sqrt(x_ * x_ + y_ * y_);
  x_ /= length; y_ /= length;
}
