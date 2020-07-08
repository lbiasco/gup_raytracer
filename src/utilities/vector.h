// This file contains the declaration of the classes Vector3D and Vector2D

#ifndef UTILITIES_VECTOR_H_
#define UTILITIES_VECTOR_H_

#include "utilities/matrix.h"

class Normal;
class Point3D;
class Point2D;

// Implementation of Vector3D utility object
class Vector3D {
  public:
    Vector3D(void);
    Vector3D(double a);
    Vector3D(double x, double y, double z);
    Vector3D(const Vector3D& v);
    Vector3D(const Normal& n);
    Vector3D(const Point3D& p);
    ~Vector3D (void);

    Vector3D& operator= (const Vector3D& rhs);
    Vector3D& operator= (const Normal& rhs); 
    Vector3D& operator= (const Point3D& rhs); 
    Vector3D operator- (void) const;
    Vector3D operator* (const double a) const;
    Vector3D operator/ (const double a) const;
    Vector3D operator+ (const Vector3D& v) const;
    Vector3D& operator+= (const Vector3D& v);
    Vector3D operator- (const Vector3D& v) const;
    double operator* (const Vector3D& b) const;
    Vector3D operator^ (const Vector3D& v) const;

    double Length(void);
    double LengthSquared(void);
    void Normalize(void); 

    double	x_, y_, z_;
};


// Inline member functions

inline Vector3D Vector3D::operator- (void) const {
  return Vector3D(-x_, -y_, -z_);    
}


inline double Vector3D::LengthSquared(void) {	
  return (x_ * x_ + y_ * y_ + z_ * z_);
}

inline Vector3D Vector3D::operator* (const double a) const {	
  return Vector3D(x_ * a, y_ * a, z_ * a);	
}

inline Vector3D Vector3D::operator/ (const double a) const {	
  return Vector3D(x_ / a, y_ / a, z_ / a);	
}

inline Vector3D Vector3D::operator+ (const Vector3D& v) const {
  return Vector3D(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}

inline Vector3D Vector3D::operator- (const Vector3D& v) const {
  return Vector3D(x_ - v.x_, y_ - v.y_, z_ - v.z_);
}

inline double Vector3D::operator* (const Vector3D& v) const {
  return (x_ * v.x_ + y_ * v.y_ + z_ * v.z_);
} 

inline Vector3D Vector3D::operator^ (const Vector3D& v) const {
  return Vector3D(y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_);
}

inline Vector3D& Vector3D::operator+= (const Vector3D& v) {
  x_ += v.x_; y_ += v.y_; z_ += v.z_;
  return (*this);
}


// Inline, non-member function

Vector3D operator* (const double a, const Vector3D& v);
inline Vector3D operator* (const double a, const Vector3D& v) {
  return Vector3D(a * v.x_, a * v.y_, a * v.z_);	
}

// Non-inline, non-member function

Vector3D operator* (const Matrix& mat, const Vector3D& v);


// Implementation of Vector3D utility object
class Vector2D {
  public:
    Vector2D(void);
    Vector2D(double a);
    Vector2D(double x, double y);
    Vector2D(const Vector2D& v);
    Vector2D(const Normal& n);
    Vector2D(const Point2D& p);
    ~Vector2D (void);

    Vector2D& operator= (const Vector2D& rhs);
    Vector2D& operator= (const Normal& rhs); 
    Vector2D& operator= (const Point2D& rhs);
    Vector2D operator- (void) const;
    Vector2D operator* (const double a) const;
    Vector2D operator/ (const double a) const;
    Vector2D operator+ (const Vector2D& v) const;
    Vector2D& operator+= (const Vector2D& v);
    Vector2D operator- (const Vector2D& v) const;
    double operator* (const Vector2D& b) const;

    double Length(void);
    double LengthSquared(void);
    void Normalize(void); 

    double	x_, y_;
};


// Inline member functions

inline Vector2D Vector2D::operator- (void) const {
  return Vector2D(-x_, -y_);    
}

inline double Vector2D::LengthSquared(void) {	
  return (x_ * x_ + y_ * y_);
}

inline Vector2D Vector2D::operator* (const double a) const {	
  return Vector2D(x_ * a, y_ * a);	
}

inline Vector2D Vector2D::operator/ (const double a) const {	
  return Vector2D(x_ / a, y_ / a);	
}

inline Vector2D Vector2D::operator+ (const Vector2D& v) const {
  return Vector2D(x_ + v.x_, y_ + v.y_);
}

inline Vector2D Vector2D::operator- (const Vector2D& v) const {
  return Vector2D(x_ - v.x_, y_ - v.y_);
}

inline double Vector2D::operator* (const Vector2D& v) const {
  return (x_ * v.x_ + y_ * v.y_);
} 

inline Vector2D& Vector2D::operator+= (const Vector2D& v) {
  x_ += v.x_; y_ += v.y_;
  return *this;
}


// Inline, non-member function

Vector2D operator* (const double a, const Vector2D& v);
inline Vector2D operator* (const double a, const Vector2D& v) {
  return Vector2D(a * v.x_, a * v.y_);	
}

#endif  // UTILITIES_VECTOR_H_
