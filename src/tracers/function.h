#ifndef TRACERS_FUNCTION_H_
#define TRACERS_FUNCTION_H_

#include <functional>

#include "tracers/tracer.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"

class Function: public Tracer {
	public:
		std::function<RGBColor (Ray)> function_ = [](Ray ray) { return RGBColor(0); };

		Function(void);
										
		Function(World* world_ptr);					
		
		virtual											
		~Function(void);

        void
        SetFunction(std::function<RGBColor (Ray)> function);
		
		virtual RGBColor	
		TraceRay(const Ray& ray) const;
};


inline void											
Function::SetFunction(std::function<RGBColor (Ray)> function) {
	function_ = function;
}

inline RGBColor	
Function::TraceRay(const Ray& ray) const {
    return function_(ray);
}

#endif  // TRACERS_FUNCTION_H_
