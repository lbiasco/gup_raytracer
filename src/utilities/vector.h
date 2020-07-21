// This file contains the declaration of the structs Vector3D and Vector2D

#ifndef UTILITIES_VECTOR_H_
#define UTILITIES_VECTOR_H_

#include <math.h>

struct Point2D;
struct Point3D;
struct Matrix;

// Declaration of Vector2D utility object
struct Vector2D {
    double	x, y;

    Vector2D() : x(0), y(0) {}
    Vector2D(double a) : x(a), y(a) {}
    Vector2D(double a, double b) : x(a), y(b) {}
    Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}
    Vector2D(const Point2D& p);

    Vector2D& operator= (const Vector2D& rhs);
    Vector2D& operator= (const Point2D& rhs);
    bool operator== (const Vector2D& v) const { return x == v.x && y == v.y; }
    Vector2D operator- () const { return Vector2D(-x, -y); }
    Vector2D operator* (const double a) const { return Vector2D(x * a, y * a); }
    Vector2D operator/ (const double a) const { return Vector2D(x / a, y / a); }
    Vector2D operator+ (const Vector2D& v) const { return Vector2D(x + v.x, y + v.y); }
    Vector2D& operator+= (const Vector2D& v);
    Vector2D operator- (const Vector2D& v) const { return Vector2D(x - v.x, y - v.y); }
    double operator* (const Vector2D& v) const { return (x * v.x + y * v.y); }

    Vector2D Hat() const;
    double Length() const { return std::sqrt(x * x + y * y); }
    double LengthSquared() const { return (x * x + y * y); };
    void Normalize();
};

// Inline member functions

inline Vector2D& Vector2D::operator= (const Vector2D& rhs) {
  if (this == &rhs)
    return *this;

  x = rhs.x; y = rhs.y;
  return *this;
}

inline Vector2D& Vector2D::operator+= (const Vector2D& v) {
  x += v.x; y += v.y;
  return *this;
}

inline void Vector2D::Normalize() {	
  double length = Length();
  x /= length; y /= length;
}

// Inline, non-member function

Vector2D operator* (const double a, const Vector2D& v);
inline Vector2D operator* (const double a, const Vector2D& v) {
  return Vector2D(a * v.x, a * v.y);	
}


// Declaration of Vector3D utility object
struct Vector3D {
    double	x, y, z;

    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(double a) : x(a), y(a), z(a) {}
    Vector3D(double a, double b, double c) : x(a), y(b), z(c) {}
    Vector3D(const Vector3D& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3D(const Point3D& p);

    static Vector3D RotateAbout(Vector3D v, Vector3D axis, double degrees);

    Vector3D& operator= (const Vector3D& rhs);
    Vector3D& operator= (const Point3D& rhs);
    bool operator== (const Vector3D& v) const { return x == v.x && y == v.y && z == v.z; }
    Vector3D operator- () const { return Vector3D(-x, -y, -z); }
    Vector3D operator* (const double a) const { return Vector3D(x * a, y * a, z * a); }
    Vector3D operator/ (const double a) const { return Vector3D(x / a, y / a, z / a); }
    Vector3D operator+ (const Vector3D& v) const { return Vector3D(x + v.x, y + v.y, z + v.z); }
    Vector3D& operator+= (const Vector3D& v);
    Vector3D operator- (const Vector3D& v) const { return Vector3D(x - v.x, y - v.y, z - v.z); }
    double operator* (const Vector3D& v) const { return (x * v.x + y * v.y + z * v.z); }
    Vector3D operator^ (const Vector3D& v) const;

    Vector3D Hat() const;
    double Length() const { return std::sqrt(x * x + y * y + z * z); }
    double LengthSquared() const { return (x * x + y * y + z * z); };
    void Normalize();
};

// Inline member functions

inline Vector3D& Vector3D::operator= (const Vector3D& rhs) {
  if (this == &rhs)
    return *this;

  x = rhs.x; y = rhs.y; z = rhs.z;
  return *this;
}

inline Vector3D& Vector3D::operator+= (const Vector3D& v) {
  x += v.x; y += v.y; z += v.z;
  return *this;
}

inline Vector3D Vector3D::operator^ (const Vector3D& v) const {
  return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

inline void Vector3D::Normalize() {	
  double length = Length();
  x /= length; y /= length; z /= length;
}

// Inline, non-member functions

inline Vector3D operator* (const double a, const Vector3D& v) {
  return Vector3D(a * v.x, a * v.y, a * v.z);	
}

// Non-member functions

Vector3D operator* (const Matrix& mat, const Vector3D& v);

#endif  // UTILITIES_VECTOR_H_
