#include "materials/glossy.h"

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

RGBColor Glossy::RayCastShade(ShadeRec& sr) {
    Vector3D wo = -sr.ray.dir();
    RGBColor L = _ambientBrdf->Rho(sr, wo) * sr.w.ambientPtr()->L(sr);
    int numLights = sr.w.lights().size();

    for (int j = 0; j < numLights; j++) {
        Vector3D wi = sr.w.lights()[j]->GetDirection(sr);
        float ndotwi = sr.normal * wi;

        if (ndotwi > 0.0) {
            L += (_diffuseBrdf->F(sr, wo, wi) + _specularBrdf->F(sr, wo, wi)) * sr.w.lights()[j]->L(sr) * ndotwi;
        }
    }

    return L;
}