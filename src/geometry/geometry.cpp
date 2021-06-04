#include "geometry/geometry.h"

Geometry::Geometry() : _materialPtr(NULL) {}

Geometry::Geometry (const Geometry& object) : _materialPtr(object._materialPtr) {}

Geometry& Geometry::operator= (const Geometry& rhs) {
    if (this == &rhs)
        return *this;
        
    _materialPtr = rhs._materialPtr;
    return *this;
}

void Geometry::samplerPtr(Sampler* ptr) {
     if (_samplerPtr) {
        delete _samplerPtr;
        _samplerPtr = NULL;
     }
     _samplerPtr = ptr;
}
