#ifndef TRACERS_FUNCTION_2D_H_
#define TRACERS_FUNCTION_2D_H_

#include "tracers/tracer.h"

class Function2D: public Tracer {
	public:
		
		Function2D(void);
										
		Function2D(World* world_ptr);					
		
		virtual											
		~Function2D(void);
		
		virtual RGBColor	
		TraceRay(const Ray& ray) const;
};

#endif  // TRACERS_FUNCTION_2D_H_
