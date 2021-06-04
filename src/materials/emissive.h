#ifndef MATERIALS_EMISSIVE_H_
#define MATERIALS_EMISSIVE_H_

#include "materials/material.h"
#include "utilities/rgb_color.h"

class Emissive : public Material {
    public:
        // Constructors, destructors
        Emissive();
        Emissive(const Emissive& mat);
        Emissive(float ls, RGBColor ce);

        // Accessors, mutators
        void SetLs(const float val) { _ls = val; }
        float GetLs() const { return _ls; }

        void SetCe(const RGBColor& c) { _ce = c; }
        RGBColor GetCe() const { return _ce; }

        // Functions
        virtual RGBColor AreaLightShade(ShadeRec& sr);
        virtual RGBColor RayCastShade(ShadeRec& sr);

        RGBColor GetLe() const;

    private:
        float _ls;       // radiance scaling factor
        RGBColor _ce;    // color
};

#endif // MATERIALS_EMISSIVE_H_
