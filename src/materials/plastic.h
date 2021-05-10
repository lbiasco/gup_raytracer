#ifndef MATERIALS_PLASTIC_H_
#define MATERIALS_PLASTIC_H_

#include "materials/material.h"
#include "brdfs/brdf.h"

class Plastic : public Material {
    public:
        Plastic(const Plastic& mat);
        Plastic(BRDF* ambient, BRDF* diffuse, BRDF* specular);

        virtual RGBColor RayCastShade(ShadeRec& sr);

    private:
        BRDF* _ambientBrdf;
        BRDF* _diffuseBrdf;
        BRDF* _specularBrdf;
};

#endif // MATERIALS_PLASTIC_H_
