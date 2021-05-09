#ifndef MATERIALS_MATTE_H_
#define MATERIALS_MATTE_H_

#include "materials/material.h"
#include "brdfs/lambertian.h"

class Matte : public Material {
public:
    Matte();

    void SetKa(const float k);
    void SetKd(const float k);
    void SetCd(const RGBColor& c);

    virtual RGBColor RayCastShade(ShadeRec& sr);

private:
    Lambertian* _ambientBrdf;
    Lambertian* _diffuseBrdf;
};

#endif // MATERIALS_MATTE_H_
