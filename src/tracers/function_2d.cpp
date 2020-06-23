#include <tgmath.h>

#include "tracers/function_2d.h"
#include "world/world.h"
#include "utilities/shade_rec.h"

// -------------------------------------------------------------------- default constructor

Function2D::Function2D(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor
		
Function2D::Function2D(World* world_ptr)
	: Tracer(world_ptr)
{}


// -------------------------------------------------------------------- destructor

Function2D::~Function2D(void) {}


// -------------------------------------------------------------------- trace_ray

RGBColor	
Function2D::TraceRay(const Ray& ray) const {
    double f = 0.5 * (1 + sin(ray.o_.x_ * ray.o_.x_ * ray.o_.y_ * ray.o_.y_));
    //double f = 0.0;
    //if (ray.o_.x_ < ray.o_.y_)
    //    f = 1.0;
    return RGBColor(f);
}
