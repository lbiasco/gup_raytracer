#include "utilities/ray.h"

Ray& Ray::operator= (const Ray& rhs) {
  if (this == &rhs)
    return (*this);
    
  origin_ = rhs.origin_; 
  dir_ = rhs.dir_; 
  return (*this);	
}
