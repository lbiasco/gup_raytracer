#include "materials/matte.h"

#include "lights/light.h"
#include "utilities/vector.h"
#include "world/world.h"

Matte::Matte() : Material(), _ambientBrdf(new Lambertian), _diffuseBrdf(new Lambertian) {}
Matte::Matte(const Matte& mat) 
    :   Material(), 
        _ambientBrdf(new Lambertian(*mat._ambientBrdf)), 
        _diffuseBrdf(new Lambertian(*mat._diffuseBrdf)) {}
Matte::Matte(float ka, float kd, RGBColor c) 
    :   Material(),
        _ambientBrdf(new Lambertian(ka, c)),
        _diffuseBrdf(new Lambertian(kd, c)) {}

void Matte::SetKa(const float k) {
    _ambientBrdf->kd(k);
}

void Matte::SetKd(const float k) {
    _diffuseBrdf->kd(k);
}

void Matte::SetCd(const RGBColor& c) {
    _ambientBrdf->cd(c);
    _diffuseBrdf->cd(c);
}

RGBColor Matte::RayCastShade(ShadeRec& sr) {
    Vector3D wo = -sr.ray.dir();
    RGBColor L = _ambientBrdf->Rho(sr, wo) * sr.w.ambientPtr()->L(sr);

    for (Light* lightPtr : sr.w.lights()) {
        Vector3D wi = lightPtr->GetDirection(sr);
        float ndotwi = sr.normal * wi;

        if (ndotwi > 0.0) {
            bool inShadow = false;

            if (receivesShadows() && lightPtr->createsShadows()) {
                Ray shadowRay(sr.hitPoint, wi);
                inShadow = lightPtr->InShadow(shadowRay, sr);
            }

            if (!inShadow) {
                L += _diffuseBrdf->F(sr, wo, wi) * lightPtr->L(sr) * ndotwi;
            }
        }
    }

    return L;
}