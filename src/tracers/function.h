#ifndef TRACERS_FUNCTION_H_
#define TRACERS_FUNCTION_H_

#include <functional>

#include "tracers/tracer.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"

// Function impementation of the Tracer object
class Function: public Tracer {
    public:
        // Constructors, destructors
        Function();    
        Function(World* worldPtr);

        void SetFunction(std::function<RGBColor (Ray)> function);
        RGBColor TraceRay(const Ray& ray) const override;

        std::function<RGBColor (Ray)> _function = [](Ray ray) { return RGBColor(0); };
};

inline void Function::SetFunction(std::function<RGBColor (Ray)> function) {
    _function = function;
}

inline RGBColor Function::TraceRay(const Ray& ray) const {
    return _function(ray);
}

#endif  // TRACERS_FUNCTION_H_
