#include "brdfs/phong.h"

#include "utilities/constants.h"

Phong::Phong() : _ks(1), _cs(1) {
    _samplerPtr = NULL;
}

Phong::Phong(const Phong& brdf) : _ks(brdf._ks), _cs(brdf._cs), _exp(brdf._exp) {
    _samplerPtr = brdf._samplerPtr;
}

Phong::Phong(float ks, float exp, RGBColor cs, Sampler* samplerPtr)
    :   _ks(ks), _cs(cs), _exp(exp) {
    _samplerPtr = samplerPtr;
}

RGBColor Phong::F(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
    RGBColor L;
    float ndotwi = sr.normal * wi;
    Vector3D r(-wi + 2.0 * sr.normal * ndotwi);
    float rdotwo = r * wo;

    if (rdotwo > 0.0) {
        L = _ks * pow(rdotwo, _exp) * _cs;
    }

    return L;
}

RGBColor Phong::SampleF(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const {
    return RGBColor(); // TODO: This function will be useful for later features
}

RGBColor Phong::Rho(const ShadeRec& sr, const Vector3D& wo) const {
    return kBlack;
}
