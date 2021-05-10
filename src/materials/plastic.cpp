#include "materials/plastic.h"

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

RGBColor Plastic::RayCastShade(ShadeRec& sr) {
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
