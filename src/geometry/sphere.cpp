#include "geometry/sphere.h"

#include <math.h>

#include "utilities/constants.h"

Sphere::Sphere(void) : Geometry(), center_(0.0), radius_(1.0) {}

Sphere::Sphere(Point3D c, double r) : Geometry(), center_(c), radius_(r) {}

Sphere::Sphere (const Sphere& sphere) 
    : Geometry(sphere), center_(sphere.center_), radius_(sphere.radius_) {}

Sphere& Sphere::operator= (const Sphere& rhs)	{
  if (this == &rhs)
    return (*this);

  Geometry::operator= (rhs);
  center_ = rhs.center_;
  radius_	= rhs.radius_;
  return *this;
}

Sphere* Sphere::Clone(void) const {
  return (new Sphere(*this));
}

bool Sphere::Hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  double    t;
  Vector3D  temp  = ray.origin() - center_;
  double    a     = ray.dir() * ray.dir();
  double    b     = 2.0 * temp * ray.dir();
  double    c     = temp * temp - radius_ * radius_;
  double    disc  = b * b - 4.0 * a * c;

  if (disc < 0.0) {
    return false;
  } else {
    double e = sqrt(disc);
    double denom = 2.0 * a;
    t = (-b - e) / denom;    // smaller root

    if (t > kEpsilon) {
      tmin = t;
      sr.normal = (temp + t * ray.dir()) / radius_;
      sr.local_hit_point = ray.origin() + t * ray.dir();
      return true;
    } 

    t = (-b + e) / denom;    // larger root
    if (t > kEpsilon) {
      tmin = t;
      sr.normal   = (temp + t * ray.dir()) / radius_;
      sr.local_hit_point = ray.origin() + t * ray.dir();
      return true;
    }
  }

  return false;
}
