#ifndef TRACERS_AREA_LIGHTING_H_
#define TRACERS_AREA_LIGHTING_H_

#include "tracers/tracer.h"

// Area light impementation of the Tracer object
class AreaLighting: public Tracer {
    public:
        // Constructors, destructors
        AreaLighting();
        AreaLighting(World* worldPtr);

        RGBColor TraceRay(const Ray& ray) const override;
};

#endif  // TRACERS_AREA_LIGHTING_H_
