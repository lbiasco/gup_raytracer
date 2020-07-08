#include "utilities/ray.h"

Ray::Ray (void) : o_(0.0), d_(0.0, 0.0, 1.0) {}

Ray::Ray (const Point3D& origin, const Vector3D& dir) : o_(origin), d_(dir) {}

Ray::Ray (const Ray& ray) : o_(ray.o_), d_(ray.d_) {}

Ray::~Ray (void) {}

Ray& Ray::operator= (const Ray& rhs) {
  if (this == &rhs)
    return (*this);
    
  o_ = rhs.o_; 
  d_ = rhs.d_; 
  return (*this);	
}
