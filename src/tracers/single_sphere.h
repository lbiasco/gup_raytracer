#ifndef TRACERS_SINGLE_SPHERE_H_
#define TRACERS_SINGLE_SPHERE_H_

#include "tracers/tracer.h"

class SingleSphere: public Tracer {
	public:
		
		SingleSphere(void);
										
		SingleSphere(World* world_ptr);					
		
		virtual											
		~SingleSphere(void);
		
		virtual RGBColor	
		TraceRay(const Ray& ray) const;
};

#endif  // TRACERS_SINGLE_SPHERE_H_
