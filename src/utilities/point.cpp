#include "utilities/point.h"

#include <math.h>

#include "utilities/vector.h"

// Implementations of struct Point2D

Point2D&  Point2D::operator= (const Point2D& rhs) {
    if (this == &rhs)
        return (*this);

    x = rhs.x; y = rhs.y;
    return (*this);
}

Vector2D Point2D::Point2D::operator- (const Point2D& p) const {
    return Vector2D(x - p.x, y - p.y);
}

Point2D Point2D::Point2D::operator+ (const Vector2D& v) const {
    return Point2D(x + v.x, y + v.y);
}

Point2D Point2D::Point2D::operator- (const Vector2D& v) const {
    return Point2D(x - v.x, y - v.y);
}


// Implementations of struct Point3D

Point3D&  Point3D::operator= (const Point3D& rhs) {
    if (this == &rhs)
        return (*this);

    x = rhs.x; y = rhs.y; z = rhs.z;
    return (*this);
}

Vector3D Point3D::operator- (const Point3D& p) const {
    return Vector3D(x - p.x, y - p.y, z - p.z);
}

Point3D Point3D::operator+ (const Vector3D& v) const {
    return Point3D(x + v.x, y + v.y, z + v.z);
}

Point3D Point3D::operator- (const Vector3D& v) const {
    return Point3D(x - v.x, y - v.y, z - v.z);
}
