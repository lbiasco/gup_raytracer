#include "utilities/ray.h"

Ray& Ray::operator= (const Ray& rhs) {
  if (this == &rhs)
    return (*this);
    
  _origin = rhs._origin; 
  _dir = rhs._dir; 
  return (*this);	
}
