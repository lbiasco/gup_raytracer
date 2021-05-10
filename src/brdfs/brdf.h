#ifndef BRDFS_BRDF_H_
#define BRDFS_BRDF_H_

#include "samplers/sampler.h"
#include "utilities/rgb_color.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"


// Base class for BRDF objects
class BRDF {
    public:
        // Virtual, no constructors/destructors

        // Functions
        virtual RGBColor F(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const = 0;
        virtual RGBColor SampleF(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const = 0;
        virtual RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const = 0;

    protected:
        Sampler* _samplerPtr;
};

#endif  // BRDFS_BRDF_H_
