#ifndef GEOMETRY_GEOMETRY_H_
#define GEOMETRY_GEOMETRY_H_

#include "materials/material.h"
#include "utilities/rgb_color.h"
#include "utilities/ray.h"
#include "utilities/shade_rec.h"
#include "utilities/constants.h"

// Base class for Geometry objects
class Geometry {	
    public:
        // Constructors, destructors
        Geometry();
        Geometry(const Geometry& object);
        Geometry&	operator= (const Geometry& rhs);

        void castsShadows(bool b) { _castsShadows = b; }
        bool castsShadows() const { return _castsShadows; }

        void material(Material* mat) { _material = mat; }
        Material* material() const { return _material; }

        virtual Geometry*	Clone() const = 0;
        virtual bool Hit(const Ray& ray, double& t, ShadeRec& s, bool skipNormal=false) const = 0;

    private:
        bool _castsShadows = true;
        Material* _material;
};

#endif  // GEOMETRY_GEOMETRY_H_
