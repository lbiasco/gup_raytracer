#ifndef MATERIALS_MATERIAL_H_
#define MATERIALS_MATERIAL_H_

#include "utilities/shade_rec.h"
#include "utilities/rgb_color.h"

// Base class for Materials
class Material {
    public:
        void receivesShadows(bool b) { _receivesShadows = b; }
        bool receivesShadows() const { return _receivesShadows; }

        // Shade function per tracer type (base material doesn't do anything with these)
        virtual RGBColor RayCastShade(ShadeRec& sr) { return RGBColor(); }
        virtual RGBColor AreaLightShade(ShadeRec& sr) { return RGBColor(); }
        virtual RGBColor PathShade(ShadeRec& sr) { return RGBColor(); }
        virtual RGBColor WhittedShade(ShadeRec &sr) { return RGBColor(); }

    private:
        bool _receivesShadows = true;
};

#endif // MATERIALS_MATERIAL_H_
