#include "tracers/multiple_objects.h"

#include "world/world.h"

MultipleObjects::MultipleObjects() : Tracer() {}

MultipleObjects::MultipleObjects(World* worldPtr) : Tracer(worldPtr) {}

RGBColor MultipleObjects::TraceRay(const Ray& ray) const {
    ShadeRec sr(worldPtr()->HitBareBonesObjects(ray)); // sr is copy constructed
        
    if (sr.hitAnObject)
        return (sr.color);
    else
        return (worldPtr()->bgColor());
}
