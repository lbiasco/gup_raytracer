#ifndef BRDFS_BLINN_H_
#define BRDFS_BLINN_H_

#include "brdfs/brdf.h"
#include "samplers/sampler.h"
#include "utilities/rgb_color.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Blinn specular implementation of BRDF
class Blinn : public BRDF {
    public:
        // Constructors, destructors
        Blinn();
        Blinn(const Blinn& brdf);
        Blinn(float ks, float exp, RGBColor cs, Sampler* samplerPtr=NULL);

        // Accessors, mutators
        void ks(float val) { _ks = val; }
        float ks() const { return _ks; }

        void cs(RGBColor val) { _cs = val; }
        RGBColor cs() const { return _cs; }

        void exp(float val) { _exp = val; }
        float exp() const { return _exp; }

        // Functions
        virtual RGBColor F(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor SampleF(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const;
        virtual RGBColor Rho(const ShadeRec& sr, const Vector3D& wo) const;

    private:
        float _ks;      // specular reflection coefficient
        RGBColor _cs;   // specular color
        float _exp;     // specular reflection power
};

#endif  // BRDFS_BLINN_H_
