#ifndef GEOMETRY_GEOMETRY_H_
#define GEOMETRY_GEOMETRY_H_

#include "materials/material.h"
#include "samplers/sampler.h"
#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Base class for Geometry objects
class Geometry {	
    public:
        // Constructors, destructors
        Geometry();
        Geometry(const Geometry& object);
        Geometry&	operator= (const Geometry& rhs);

        void castsShadows(bool b) { _castsShadows = b; }
        bool castsShadows() const { return _castsShadows; }

        void materialPtr(Material* mat) { _materialPtr = mat; }
        Material* materialPtr() const { return _materialPtr; }
        
        virtual void samplerPtr(Sampler* ptr);

        virtual Geometry* Clone() const = 0;
        virtual Vector3D GetNormal(const Vector3D& p) = 0;
        virtual bool Hit(const Ray& ray, double& t, ShadeRec& s, bool skipNormal=false) const = 0;
        virtual float Pdf(ShadeRec& sr) = 0;
        virtual Vector3D Sample() = 0;

    protected:
        Sampler* _samplerPtr;

    private:
        bool _castsShadows = true;
        Material* _materialPtr;
};

#endif  // GEOMETRY_GEOMETRY_H_
