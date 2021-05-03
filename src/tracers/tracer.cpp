#include "tracers/tracer.h"

Tracer::Tracer() : _worldPtr(NULL) {}

Tracer::Tracer(World* worldPtr) : _worldPtr(worldPtr) {}

Tracer::~Tracer() {
  if (_worldPtr)
    _worldPtr = NULL;
}

RGBColor Tracer::TraceRay(const Ray& ray) const {
  return (kBlack);
}

RGBColor Tracer::TraceRay(const Ray ray, const int depth) const {
  return TraceRay(ray); // Temporary redirect while depth is not used
}
