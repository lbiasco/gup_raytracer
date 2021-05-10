#include "geometry/plane.h"

#include "utilities/constants.h"

Plane::Plane(void) : Geometry(), _point(0.0), _normal(0, 1, 0) {}

Plane::Plane(const Vector3D& p, const Vector3D& n) 
    : Geometry(), _point(p), _normal(n) {
    _normal.Normalize();
}

Plane::Plane(const Plane& plane) 
    : Geometry(plane), _point(plane.point()), _normal(plane.normal()) {}

Plane& Plane::operator= (const Plane& rhs) {
    if (this == &rhs)
        return (*this);

    Geometry::operator= (rhs);
    _point = rhs.point();
    _normal = rhs.normal();
    return *this;
}

Plane* Plane::Clone(void) const {
    return (new Plane(*this));
}

bool Plane::Hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
    float t = (_point - ray.origin()) * _normal / (ray.dir() * _normal); 

    if (t > kEpsilon) {
        tmin = t;
        sr.normal = _normal;
        sr.localHitPoint = ray.origin() + t * ray.dir();
        return (true);	
    }
    return(false);
}
