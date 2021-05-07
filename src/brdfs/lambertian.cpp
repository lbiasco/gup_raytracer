#include "brdfs/lambertian.h"

#include "utilities/constants.h"

Lambertian::Lambertian(Sampler* samplerPtr, float kd, RGBColor cd)
    :  _kd(kd), _cd(cd) {
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
