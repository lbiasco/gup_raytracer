#include "geometry/geometry.h"

Geometry::Geometry() : _material(NULL) {}

Geometry::Geometry (const Geometry& object) : _material(object._material) {}

Geometry&	Geometry::operator= (const Geometry& rhs) {
    if (this == &rhs)
        return *this;
        
    _material = rhs._material;
    return *this;
}
