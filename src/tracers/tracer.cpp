#include "tracers/tracer.h"

Tracer::Tracer(void) : world_ptr_(NULL) {}

Tracer::Tracer(World* world_ptr) : world_ptr_(world_ptr) {}

Tracer::~Tracer(void) {
  if (world_ptr_)
    world_ptr_ = NULL;
}

RGBColor Tracer::TraceRay(const Ray& ray) const {
  return (kBlack);
}

RGBColor Tracer::TraceRay(const Ray ray, const int depth) const {
  return TraceRay(ray); // Temporary redirect while depth is not used
}
