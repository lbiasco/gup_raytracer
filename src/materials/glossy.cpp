#include "materials/glossy.h"

#include "lights/light.h"
#include "utilities/vector.h"
#include "world/world.h"

Glossy::Glossy() 
    :   Material(), 
        _ambientBrdf(new Lambertian), 
        _diffuseBrdf(new Lambertian),
        _specularBrdf(new Phong) {}

Glossy::Glossy(const Glossy& mat) 
    :   Material(), 
        _ambientBrdf(new Lambertian(*mat._ambientBrdf)), 
        _diffuseBrdf(new Lambertian(*mat._diffuseBrdf)),
        _specularBrdf(new Phong(*mat._specularBrdf)) {}

Glossy::Glossy(float ka, float kd, float ks, float exp, RGBColor c) 
    :   Material(),
        _ambientBrdf(new Lambertian(ka, c)),
        _diffuseBrdf(new Lambertian(kd, c)),
        _specularBrdf(new Phong(ks, exp, c)) {}

void Glossy::SetKa(const float k) {
    _ambientBrdf->kd(k);
}

void Glossy::SetKd(const float k) {
    _diffuseBrdf->kd(k);
}

void Glossy::SetKs(const float k) {
    _specularBrdf->ks(k);
}

void Glossy::SetCa(const RGBColor& c) {
    _ambientBrdf->cd(c);
}

void Glossy::SetCd(const RGBColor& c) {
    _diffuseBrdf->cd(c);
}

void Glossy::SetCs(const RGBColor& c) {
    _specularBrdf->cs(c);
}

void Glossy::SetExp(const float exp) {
    _specularBrdf->exp(exp);
}

RGBColor Glossy::AreaLightShade(ShadeRec& sr) {
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
                L += (_diffuseBrdf->F(sr, wo, wi) + _specularBrdf->F(sr, wo, wi)) * lightPtr->L(sr) * lightPtr->G(sr) * ndotwi / lightPtr->Pdf(sr);
            }
        }
    }

    return L;
}

RGBColor Glossy::RayCastShade(ShadeRec& sr) {
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
                L += (_diffuseBrdf->F(sr, wo, wi) + _specularBrdf->F(sr, wo, wi)) * lightPtr->L(sr) * ndotwi;
            }
        }
    }

    return L;
}
