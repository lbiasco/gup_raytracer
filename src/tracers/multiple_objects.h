#ifndef TRACERS_MULTIPLE_OBJECTS_H_
#define TRACERS_MULTIPLE_OBJECTS_H_

#include "tracers/tracer.h"

// MultipleObjects impementation of the Tracer object
class MultipleObjects: public Tracer {
  public:
    // Constructors, destructors
    MultipleObjects();
    MultipleObjects(World* worldPtr);

    RGBColor TraceRay(const Ray& ray) const override;
};

#endif  // TRACERS_MULTIPLE_OBJECTS_H_
