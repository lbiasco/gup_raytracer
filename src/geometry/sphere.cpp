#include "geometry/sphere.h"

#include <math.h>

#include "utilities/constants.h"

Sphere::Sphere(void) : Geometry(), center_(0.0), radius_(1.0) {}

Sphere::Sphere(Point3D c, double r) : Geometry(), center_(c), radius_(r) {}

Sphere::Sphere (const Sphere& sphere) 
    : Geometry(sphere), center_(sphere.center_), radius_(sphere.radius_) {}

Sphere::~Sphere(void) {}

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
  Vector3D  temp  = ray.o_ - center_;
  double    a     = ray.d_ * ray.d_;
  double    b     = 2.0 * temp * ray.d_;
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
      sr.normal_ = (temp + t * ray.d_) / radius_;
      sr.local_hit_point_ = ray.o_ + t * ray.d_;
      return true;
    } 

    t = (-b + e) / denom;    // larger root
    if (t > kEpsilon) {
      tmin = t;
      sr.normal_   = (temp + t * ray.d_) / radius_;
      sr.local_hit_point_ = ray.o_ + t * ray.d_;
      return true;
    } 
  }

  return false;
}
