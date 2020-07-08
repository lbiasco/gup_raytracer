#include "tracers/multiple_objects.h"

#include "world/world.h"

MultipleObjects::MultipleObjects(void) : Tracer() {}

MultipleObjects::MultipleObjects(World* world_ptr) : Tracer(world_ptr) {}

MultipleObjects::~MultipleObjects(void) {}

RGBColor MultipleObjects::TraceRay(const Ray& ray) const {
  ShadeRec sr(world_ptr_->HitBareBonesObjects(ray)); // sr is copy constructed
    
  if (sr.hit_an_object_)
    return (sr.color_);
  else
    return (world_ptr_->background_color_);
}
