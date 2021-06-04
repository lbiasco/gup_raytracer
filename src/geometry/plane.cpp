#include "geometry/plane.h"

const double Plane::kEpsilon = 0.0001;

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

Vector3D Plane::GetNormal(const Vector3D& p) {
    return _normal;
}

bool Plane::Hit(const Ray& ray, double& tmin, ShadeRec& sr, bool skipNormal) const {	
    float t = (_point - ray.origin()) * _normal / (ray.dir() * _normal); 

    if (t > kEpsilon) {
        tmin = t;
        sr.localHitPoint = ray.origin() + t * ray.dir();
        if (!skipNormal) {
            sr.normal = _normal;
        }
        return true;	
    }
    return false;
}

// Pdf and Sample are nonsense functions atm since they are only used by AreaLight, 
// which isn't supported with Plane geometry
float Plane::Pdf(ShadeRec& sr) {
    return 1;
}

Vector3D Plane::Sample() {
    return Vector3D();
}
