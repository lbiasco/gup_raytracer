#include "geometry/geometry.h"

Geometry::Geometry() : color_(kBlack) {}

Geometry::Geometry (const Geometry& object) : color_(object.color_) {}

Geometry&	Geometry::operator= (const Geometry& rhs) {
  if (this == &rhs)
    return *this;
    
  color_ = rhs.color_;
  return *this;
}
