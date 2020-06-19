#include "tracers/tracer.h"

// -------------------------------------------------------------------- default constructor

Tracer::Tracer(void)
	: world_ptr_(NULL)
{}


// -------------------------------------------------------------------- constructor

Tracer::Tracer(World* world_ptr)
	: world_ptr_(world_ptr)
{}



// -------------------------------------------------------------------- destructor

Tracer::~Tracer(void) {
	if (world_ptr_)
		world_ptr_ = NULL;
}


// -------------------------------------------------------------------- TraceRay

RGBColor	
Tracer::TraceRay(const Ray& ray) const {
	return (kBlack);
}


// -------------------------------------------------------------------- TraceRay

RGBColor	
Tracer::TraceRay(const Ray ray, const int depth) const {
	return (kBlack);
}



