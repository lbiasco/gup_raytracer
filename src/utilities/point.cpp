#include "utilities/point.h"

#include <math.h>


// Point3D

Point3D::Point3D() : x_(0), y_(0), z_(0) {}

Point3D::Point3D(const double c) : x_(c), y_(c), z_(c) {}

Point3D::Point3D(const double x, const double y, const double z) 
    : x_(x), y_(y), z_(z) {}

Point3D::Point3D(const Point3D& p) : x_(p.x_), y_(p.y_), z_(p.z_) {}

Point3D::~Point3D() {}

Point3D& Point3D::operator= (const Point3D& rhs) {
  if (this == &rhs)
    return (*this);

  x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_;
  return (*this);
}

double Point3D::Distance(const Point3D& p) const {
  return sqrt((x_ - p.x_) * (x_ - p.x_) 
          + (y_ - p.y_) * (y_ - p.y_)
          + (z_ - p.z_) * (z_ - p.z_));
}

Point3D operator* (const Matrix& mat, const Point3D& p) {
  return (Point3D(mat.m_[0][0] * p.x_ + mat.m_[0][1] * p.y_ + mat.m_[0][2] * p.z_ + mat.m_[0][3],
          mat.m_[1][0] * p.x_ + mat.m_[1][1] * p.y_ + mat.m_[1][2] * p.z_ + mat.m_[1][3],
          mat.m_[2][0] * p.x_ + mat.m_[2][1] * p.y_ + mat.m_[2][2] * p.z_ + mat.m_[2][3]));
}


// Point2D

Point2D::Point2D() : x_(0), y_(0) {}

Point2D::Point2D(const double c) :x_(c), y_(c) {}

Point2D::Point2D(const double x, const double y) : x_(x), y_(y) {}

Point2D::Point2D(const Point2D& p) : x_(p.x_), y_(p.y_) {}

Point2D::~Point2D() {}

Point2D&  Point2D::operator= (const Point2D& rhs) {
  if (this == &rhs)
    return (*this);

  x_ = rhs.x_; y_ = rhs.y_;
  return (*this);
}
