#include "geometry/plane.h"
#include "utilities/constants.h"

Plane::Plane(void) : Geometry(), a_(0.0), n_(0, 1, 0) {}

Plane::Plane(const Point3D& point, const Normal& normal) 
    : Geometry(), a_(point), n_(normal) {
  n_.Normalize();
}

Plane::Plane(const Plane& plane) : Geometry(plane), a_(plane.a_), n_(plane.n_) {}

Plane::~Plane(void) {}

Plane& Plane::operator= (const Plane& rhs) {
  if (this == &rhs)
    return (*this);

  Geometry::operator= (rhs);
  a_ = rhs.a_;
  n_ = rhs.n_;
  return *this;
}

Plane* Plane::Clone(void) const {
  return (new Plane(*this));
}

bool Plane::Hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
  float t = (a_ - ray.o_) * n_ / (ray.d_ * n_); 

  if (t > kEpsilon) {
    tmin = t;
    sr.normal_ = n_;
    sr.local_hit_point_ = ray.o_ + t * ray.d_;
    return (true);	
  }
  return(false);
}
