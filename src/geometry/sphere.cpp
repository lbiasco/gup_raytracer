#include "geometry/sphere.h"

#include <math.h>

#include "utilities/constants.h"

Sphere::Sphere(void) : Geometry(), _center(0.0), _radius(1.0) {}

Sphere::Sphere(Point3D c, double r) : Geometry(), _center(c), _radius(r) {}

Sphere::Sphere (const Sphere& sphere) 
    : Geometry(sphere), _center(sphere._center), _radius(sphere._radius) {}

Sphere& Sphere::operator= (const Sphere& rhs)	{
    if (this == &rhs)
        return (*this);

    Geometry::operator= (rhs);
    _center = rhs._center;
    _radius	= rhs._radius;
    return *this;
}

Sphere* Sphere::Clone(void) const {
    return (new Sphere(*this));
}

bool Sphere::Hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double    t;
    Vector3D  temp  = ray.origin() - _center;
    double    a     = ray.dir() * ray.dir();
    double    b     = 2.0 * temp * ray.dir();
    double    c     = temp * temp - _radius * _radius;
    double    disc  = b * b - 4.0 * a * c;

    if (disc < 0.0) {
        return false;
    } else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal = (temp + t * ray.dir()) / _radius;
            sr.localHitPoint = ray.origin() + t * ray.dir();
            return true;
        } 

        t = (-b + e) / denom;    // larger root
        if (t > kEpsilon) {
            tmin = t;
            sr.normal   = (temp + t * ray.dir()) / _radius;
            sr.localHitPoint = ray.origin() + t * ray.dir();
            return true;
        }
    }

    return false;
}
