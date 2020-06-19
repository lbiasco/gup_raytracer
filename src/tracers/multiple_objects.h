#ifndef TRACERS_MULTIPLE_OBJECTS_H_
#define TRACERS_MULTIPLE_OBJECTS_H_

#include "tracers/tracer.h"

class MultipleObjects: public Tracer {
	public:
		
		MultipleObjects(void);							
		
		MultipleObjects(World* world_ptr);				
	
		virtual											
		~MultipleObjects(void);
						
		virtual RGBColor	
		TraceRay(const Ray& ray) const;
};

#endif  // TRACERS_MULTIPLE_OBJECTS_H_
