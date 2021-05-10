#ifndef LIGHTS_LIGHT_H_
#define LIGHTS_LIGHT_H_

#include "utilities/rgb_color.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"


// Base class for Light objects
class Light {
    public:
        // Virtual, no constructors/destructors

        // Functions
        virtual Vector3D GetDirection(ShadeRec& sr) = 0;
        virtual RGBColor L(ShadeRec& sr) = 0;

    protected:
        bool _shadows;
};

#endif  // LIGHTS_LIGHT_H_
