#ifndef MATERIALS_GLOSSY_H_
#define MATERIALS_GLOSSY_H_

#include "materials/material.h"
#include "brdfs/blinn.h"
#include "brdfs/phong.h"
#include "brdfs/lambertian.h"

class Glossy : public Material {
    public:
        Glossy();
        Glossy(const Glossy& mat);
        Glossy(float ka, float kd, float ks, float exp, RGBColor c);

        void SetKa(const float k);
        void SetKd(const float k);
        void SetKs(const float k);
        
        void SetCa(const RGBColor& c);
        void SetCd(const RGBColor& c);
        void SetCs(const RGBColor& c);

        void SetExp(const float exp);

        virtual RGBColor RayCastShade(ShadeRec& sr);

    private:
        Lambertian*     _ambientBrdf;
        Lambertian*     _diffuseBrdf;
        Phong* _specularBrdf;
};

#endif // MATERIALS_GLOSSY_H_
