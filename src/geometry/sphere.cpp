#include "geometry/sphere.h"

#include <math.h>

#include "utilities/constants.h"
#include "utilities/random.h"

const double Sphere::kEpsilon = 0.0001;

Sphere::Sphere(void) : Geometry(), _center(0.0), _radius(1.0) {
    _CalculateAreaInv();
}

Sphere::Sphere(Vector3D c, double r) : Geometry(), _center(c), _radius(r) {
    _CalculateAreaInv();
}

Sphere::Sphere (const Sphere& sphere) 
    : Geometry(sphere), _center(sphere._center), _radius(sphere._radius) {
    _CalculateAreaInv();
}

Sphere& Sphere::operator= (const Sphere& rhs)	{
    if (this == &rhs)
        return (*this);

    _center = rhs._center;
    _radius	= rhs._radius;
    _areaInv = rhs._areaInv;
    return *this;
}

void Sphere::radius(double r) {
    _radius = r;
    _CalculateAreaInv();
}

void Sphere::samplerPtr(Sampler* ptr) {
     if (_samplerPtr) {
        delete _samplerPtr;
        _samplerPtr = NULL;
     }
     _samplerPtr = ptr;
     _samplerPtr->MapSamplesToHemisphere(1);
}


Sphere* Sphere::Clone(void) const {
    return (new Sphere(*this));
}

Vector3D Sphere::GetNormal(const Vector3D& p) {
    return (p - _center).Normalized();
}

bool Sphere::Hit(const Ray& ray, double& tmin, ShadeRec& sr, bool skipNormal) const {
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
            sr.localHitPoint = ray.origin() + t * ray.dir();
            if (!skipNormal) {
                sr.normal = (temp + t * ray.dir()) / _radius;
            }
            return true;
        } 

        t = (-b + e) / denom;    // larger root
        if (t > kEpsilon) {
            tmin = t;
            sr.localHitPoint = ray.origin() + t * ray.dir();
            if (!skipNormal) {
                sr.normal   = (temp + t * ray.dir()) / _radius;
            }
            return true;
        }
    }

    return false;
}

float Sphere::Pdf(ShadeRec& sr) {
    return _areaInv;
}

Vector3D Sphere::Sample() {
    Vector3D samplePoint = _samplerPtr->SampleHemisphere();
    // Randomly flip sample point
    if (RandInt(2) == 0) {
        samplePoint.z *= -1;
    }
    return (_radius * samplePoint);
}

void Sphere::_CalculateAreaInv() {
    _areaInv = 1 / (4 * kPi * _radius * _radius);
}