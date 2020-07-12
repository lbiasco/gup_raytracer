#include "geometry/plane.h"

#include "utilities/constants.h"

Plane::Plane(void) : Geometry(), point_(0.0), normal_(0, 1, 0) {}

Plane::Plane(const Point3D& p, const Vector3D& n) 
    : Geometry(), point_(p), normal_(n) {
  normal_.Normalize();
}

Plane::Plane(const Plane& plane) 
    : Geometry(plane), point_(plane.point()), normal_(plane.normal()) {}

Plane& Plane::operator= (const Plane& rhs) {
  if (this == &rhs)
    return (*this);

  Geometry::operator= (rhs);
  point_ = rhs.point();
  normal_ = rhs.normal();
  return *this;
}

Plane* Plane::Clone(void) const {
  return (new Plane(*this));
}

bool Plane::Hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
  float t = (point_ - ray.origin()) * normal_ / (ray.dir() * normal_); 

  if (t > kEpsilon) {
    tmin = t;
    sr.normal = normal_;
    sr.local_hit_point = ray.origin() + t * ray.dir();
    return (true);	
  }
  return(false);
}
