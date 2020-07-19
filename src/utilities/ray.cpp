#include "utilities/ray.h"

Ray& Ray::operator= (const Ray& rhs) {
  if (this == &rhs)
    return (*this);
    
  origin_ = rhs.origin_; 
  dir_ = rhs.dir_; 
  return (*this);	
}

Point3D Ray::Intersect(const Ray& ray) {
  Vector3D dir3 = ray.origin() - origin_;
  Vector3D cross_product_1 = ray.dir() ^ dir3;
  Vector3D cross_product_2 = dir_ ^ ray.dir();

  double length_1 = cross_product_1.Length();
  double length_2 = cross_product_2.Length();
  if (length_1 == 0 || length_2 == 0)
    return NULL;

  int dir_sign = 1;
  if (cross_product_1 / length_1 == -cross_product_2 / length_2)
    dir_sign = -1;

  Point3D result = origin_ + dir_sign * dir_ * (length_1 / length_2);
  return result;
}
