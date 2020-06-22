#include "tracers/single_sphere.h"
#include "world/world.h"
#include "utilities/shade_rec.h"

// -------------------------------------------------------------------- default constructor

SingleSphere::SingleSphere(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor
		
SingleSphere::SingleSphere(World* world_ptr)
	: Tracer(world_ptr)
{}


// -------------------------------------------------------------------- destructor

SingleSphere::~SingleSphere(void) {}


// -------------------------------------------------------------------- trace_ray

RGBColor	
SingleSphere::TraceRay(const Ray& ray) const {
	ShadeRec	sr(*world_ptr_); 	// not used
	double    	t;  				// not used
	
	if (world_ptr_->sphere_.Hit(ray, t, sr))		
		return (RGBColor(0.0, 0.0, 1.0));  
	else
		return (kBlack);   
}
