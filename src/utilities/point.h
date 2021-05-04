// This file contains the declaration of the classes Point3D and Point2D

#ifndef UTILITIES_POINT_H_
#define UTILITIES_POINT_H_

#include <math.h>

struct Vector2D;
struct Vector3D;

// Declaration of Point2D utility object
struct Point2D {
    double x, y;

    Point2D() : x(0), y(0) {}
    Point2D(double a) : x(a), y(a) {}
    Point2D(double a, double b) : x(a), y(b) {}
    Point2D(const Point2D& p) : x(p.x), y(p.y) {}
    
    Point2D& operator= (const Point2D& p);
    Point2D operator- (void) const { return Point2D(-x, -y); }
    Vector2D operator- (const Point2D& p) const;
    Point2D operator+ (const Vector2D& v) const;
    Point2D operator- (const Vector2D& v) const;
    Point2D operator* (const double a) const {return Point2D(x * a, y * a); }
};

// Inline, non-member functions
inline Point2D operator* (const double a, const Point2D& p) {
    return Point2D(a * p.x, a * p.y);
}


// Declaration of Point3D utility object
struct Point3D {
    double x, y, z;

    Point3D() : x(0), y(0), z(0) {}
    Point3D(double c) : x(c), y(c), z(c) {}
    Point3D(double a, double b, double c) : x(a), y(b), z(c) {}
    Point3D(const Point3D& p) : x(p.x), y(p.y), z(p.z) {}
    
    Point3D& operator= (const Point3D& p);
    Point3D operator- (void) const { return Point3D(-x, -y, -z); }
    Vector3D operator- (const Point3D& p) const;
    Point3D operator+ (const Vector3D& v) const;
    Point3D operator- (const Vector3D& v) const;
    Point3D operator* (const double a) const { return Point3D(x * a, y * a, z * a); }
    
    double DistanceSquared(const Point3D& p) const;
    double Distance(const Point3D& p) const;
};

// Inline member functions
inline double Point3D::DistanceSquared(const Point3D& p) const {
    return std::sqrt((x - p.x) * (x - p.x) 
        + (y - p.y) * (y - p.y)
        + (z - p.z) * (z - p.z) );
}

// Inline, non-member functions
inline Point3D operator* (const double a, const Point3D& p) {
    return Point3D(a * p.x, a * p.y, a * p.z);
}


#endif  // UTILITIES_POINT_H_
