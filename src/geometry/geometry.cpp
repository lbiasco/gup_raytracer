#include "geometry/geometry.h"

Geometry::Geometry() : _color(kBlack) {}

Geometry::Geometry (const Geometry& object) : _color(object._color) {}

Geometry&	Geometry::operator= (const Geometry& rhs) {
    if (this == &rhs)
        return *this;
        
    _color = rhs._color;
    return *this;
}
