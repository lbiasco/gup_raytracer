#ifndef TRACERS_RAYCAST_H_
#define TRACERS_RAYCAST_H_

#include "tracers/tracer.h"

// RayCast impementation of the Tracer object
class RayCast: public Tracer {
    public:
        // Constructors, destructors
        RayCast();
        RayCast(World* worldPtr);

        RGBColor TraceRay(const Ray& ray) const override;
};

#endif  // TRACERS_RAYCAST_H_
