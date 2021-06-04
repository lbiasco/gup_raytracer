#include "tracers/area_lighting.h"

#include "materials/material.h"
#include "world/world.h"

AreaLighting::AreaLighting() : Tracer() {}

AreaLighting::AreaLighting(World* worldPtr) : Tracer(worldPtr) {}

RGBColor AreaLighting::TraceRay(const Ray& ray) const {
    ShadeRec sr(worldPtr()->HitObjects(ray)); // sr is copy constructed
        
    if (sr.hitAnObject) {
        sr.ray = ray;
        return sr.materialPtr->AreaLightShade(sr);
    } else {
        return (worldPtr()->bgColor());
    }
}
