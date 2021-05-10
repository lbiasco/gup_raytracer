#include "brdfs/blinn.h"

#include "utilities/constants.h"

Blinn::Blinn() : _ks(1), _cs(1) {
    _samplerPtr = NULL;
}

Blinn::Blinn(const Blinn& brdf) : _ks(brdf._ks), _cs(brdf._cs), _exp(brdf._exp) {
    _samplerPtr = brdf._samplerPtr;
}

Blinn::Blinn(float ks, float exp, RGBColor cs, Sampler* samplerPtr)
    :   _ks(ks), _cs(cs), _exp(exp) {
    _samplerPtr = samplerPtr;
}

RGBColor Blinn::F(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
    RGBColor L;

    Vector3D h((wi + wo)/(wi + wo).Length());
    float ndoth = sr.normal * h;

    if (ndoth > 0.0) { // Is < 0 even possible?
        L = _ks * pow(ndoth, _exp) * _cs;
    }

    return L;
}

RGBColor Blinn::SampleF(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const {
    return RGBColor(); // TODO: This function will be useful for later features
}

RGBColor Blinn::Rho(const ShadeRec& sr, const Vector3D& wo) const {
    return kBlack;
}
