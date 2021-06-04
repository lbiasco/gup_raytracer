#ifndef LIGHTS_LIGHT_H_
#define LIGHTS_LIGHT_H_

#include "utilities/rgb_color.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"


// Base class for Light objects
class Light {
    public:
        // Virtual, no constructors/destructors
        // Accessors, mutators
        void createsShadows(bool b) { _createsShadows = b; }
        bool createsShadows() const { return _createsShadows; }

        // Functions
        virtual Vector3D GetDirection(ShadeRec& sr) = 0;
        virtual bool InShadow(const Ray& ray, const ShadeRec& sr) const = 0;
        virtual RGBColor L(ShadeRec& sr) = 0;
        virtual float G(ShadeRec& sr) const = 0;
        virtual float Pdf(ShadeRec& sr) = 0;

    protected:
        bool _createsShadows = true;
};

#endif  // LIGHTS_LIGHT_H_
