#ifndef BRDFS_LAMBERTIAN_H_
#define BRDFS_LAMBERTIAN_H_

#include "brdfs/brdf.h"
#include "samplers/sampler.h"
#include "utilities/rgb_color.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Lambertian implementation of BRDF
class Lambertian : public BRDF {
public:
    // Constructors, destructors
    Lambertian();
    Lambertian(const Lambertian& brdf);
    Lambertian(float kd, RGBColor cd, Sampler* samplerPtr=NULL);

    // Accessors, mutators
    void kd(float val) { _kd = val; }
    float kd() const { return _kd; }

    void cd(RGBColor val) { _cd = val; }
    RGBColor cd() const { return _cd; }

    // Functions
    virtual RGBColor F(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;
    virtual RGBColor SampleF(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const;
    virtual RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const;

private:
    float _kd;       // diffuse reflection coefficient
    RGBColor _cd;    // diffuse color
};

#endif  // BRDFS_LAMBERTIAN_H_
