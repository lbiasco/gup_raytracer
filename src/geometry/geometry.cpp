#include "geometry/geometry.h"

Geometry::Geometry(void) : color_(kBlack) {}

Geometry::Geometry (const Geometry& object) : color_(object.color_) {}

Geometry::~Geometry (void) {}

Geometry&	Geometry::operator= (const Geometry& rhs) {
  if (this == &rhs)
    return *this;
    
  color_ = rhs.color_;
  return *this;
}
