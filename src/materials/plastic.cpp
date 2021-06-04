#include "materials/plastic.h"

#include "lights/light.h"
#include "utilities/vector.h"
#include "world/world.h"

Plastic::Plastic(const Plastic& mat) 
    :   Material(),
        _ambientBrdf(mat._ambientBrdf),
        _diffuseBrdf(mat._diffuseBrdf),
        _specularBrdf(mat._specularBrdf) {}

Plastic::Plastic(BRDF* ambient, BRDF* diffuse, BRDF* specular) 
    :   Material(),
        _ambientBrdf(ambient),
        _diffuseBrdf(diffuse),
        _specularBrdf(specular) {}

RGBColor Plastic::AreaLightShade(ShadeRec& sr) {
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

RGBColor Plastic::RayCastShade(ShadeRec& sr) {
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
