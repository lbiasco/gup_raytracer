#include "tracers/multiple_objects.h"

#include "world/world.h"

MultipleObjects::MultipleObjects() : Tracer() {}

MultipleObjects::MultipleObjects(World* world_ptr) : Tracer(world_ptr) {}

RGBColor MultipleObjects::TraceRay(const Ray& ray) const {
  ShadeRec sr(world_ptr()->HitBareBonesObjects(ray)); // sr is copy constructed
    
  if (sr.hit_an_object)
    return (sr.color);
  else
    return (world_ptr()->bg_color());
}
