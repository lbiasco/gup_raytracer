#include "brdfs/lambertian.h"

#include "utilities/constants.h"

Lambertian::Lambertian() :  _kd(1), _cd(1) {
    _samplerPtr = NULL;
}

Lambertian::Lambertian(const Lambertian& brdf) : _kd(brdf._kd), _cd(brdf._cd) {
    _samplerPtr = brdf._samplerPtr;
}

Lambertian::Lambertian(float kd, RGBColor cd, Sampler* samplerPtr)
    :   _kd(kd), _cd(cd) {
    _samplerPtr = samplerPtr;
}

RGBColor Lambertian::F(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const {
    return (_kd * _cd * kInvPi);
}

RGBColor Lambertian::SampleF(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const {
    return RGBColor(); // TODO: This function will be useful for later features
}

RGBColor Lambertian::Rho(const ShadeRec& sr, const Vector3D& wo) const {
    return (_kd * _cd);
}
