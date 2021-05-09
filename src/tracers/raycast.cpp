#include "tracers/raycast.h"

#include "materials/material.h"
#include "world/world.h"

RayCast::RayCast() : Tracer() {}

RayCast::RayCast(World* worldPtr) : Tracer(worldPtr) {}

RGBColor RayCast::TraceRay(const Ray& ray) const {
    ShadeRec sr(worldPtr()->HitObjects(ray)); // sr is copy constructed
        
    if (sr.hitAnObject) {
        sr.ray = ray;   // for specular reflection (Ch 15)
        return sr.materialPtr->RayCastShade(sr);
    } else {
        return (worldPtr()->bgColor());
    }
}
