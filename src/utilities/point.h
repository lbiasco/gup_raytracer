// This file contains the declaration of the classes Point3D and Point2D

#ifndef UTILITIES_POINT_H_
#define UTILITIES_POINT_H_

#include "utilities/matrix.h"
#include "utilities/vector.h"

// Implementation of Point3D utility object
class Point3D {
  public:
    Point3D();
    Point3D(const double c);
    Point3D(const double x, const double y, const double z);
    Point3D(const Point3D& p);
    ~Point3D();
    
    Point3D& operator= (const Point3D& p);
    Point3D operator- (void) const;
    Vector3D operator- (const Point3D& p) const;
    Point3D operator+ (const Vector3D& v) const;
    Point3D operator- (const Vector3D& v) const;
    Point3D operator* (const double a) const;
    
    double DistanceSquared(const Point3D& p) const;
    double Distance(const Point3D& p) const;

    double x_, y_, z_;
};


// Inline, member functions
inline Point3D  Point3D::operator- (void) const {
  return Point3D(-x_, -y_, -z_);
}

inline Vector3D Point3D::operator- (const Point3D& p) const {
  return Vector3D(x_ - p.x_,y_ - p.y_,z_ - p.z_);
}

inline Point3D Point3D::operator+ (const Vector3D& v) const {
  return Point3D(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}

inline Point3D Point3D::operator- (const Vector3D& v) const {
  return Point3D(x_ - v.x_, y_ - v.y_, z_ - v.z_);
}

inline Point3D Point3D::operator* (const double a) const {
  return Point3D(x_ * a, y_ * a, z_ * a);
}

inline double Point3D::DistanceSquared(const Point3D& p) const {
  return ((x_ - p.x_) * (x_ - p.x_) 
      + (y_ - p.y_) * (y_ - p.y_)
      + (z_ - p.z_) * (z_ - p.z_) );
}

// Inline, non-member functions
Point3D operator* (double a, const Point3D& p);
inline Point3D operator* (double a, const Point3D& p) {
  return Point3D(a * p.x_, a * p.y_, a * p.z_);
}

// Non-inline, non-member functions
Point3D operator* (const Matrix& mat, const Point3D& p);


// Implementation of Point2D utility object
class Point2D {
  public:
    Point2D();
    Point2D(const double c);
    Point2D(const double x, const double y);
    Point2D(const Point2D& p);
    ~Point2D();
    
    Point2D& operator= (const Point2D& p);
    Point2D operator- (void) const;
    Vector2D operator- (const Point2D& p) const;
    Point2D operator+ (const Vector2D& v) const;
    Point2D operator- (const Vector2D& v) const;
    Point2D operator* (const double a) const;

    double x_, y_;
};

// Inline member functions
inline Point2D Point2D::operator- (void) const {
  return Point2D(-x_, -y_);
}

inline Vector2D  Point2D::operator- (const Point2D& p) const {
  return Vector2D(x_ - p.x_,y_ - p.y_);
}

inline Point2D Point2D::operator+ (const Vector2D& v) const {
  return Point2D(x_ + v.x_, y_ + v.y_);
}

inline Point2D Point2D::operator- (const Vector2D& v) const {
  return Point2D(x_ - v.x_, y_ - v.y_);
}

inline Point2D Point2D::operator* (const double a) const {
  return Point2D(x_ * a, y_ * a);
}

// Inline, non-member functions
Point2D operator* (double a, const Point2D& p);
inline Point2D operator* (double a, const Point2D& p) {
  return Point2D(a * p.x_, a * p.y_);
}

#endif  // UTILITIES_POINT_H_
