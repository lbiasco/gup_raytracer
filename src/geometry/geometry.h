#ifndef GEOMETRY_GEOMETRY_H_
#define GEOMETRY_GEOMETRY_H_

#include "materials/material.h"
#include "utilities/rgb_color.h"
#include "utilities/point.h"
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

    void material(Material* mat) { _material = mat; }
    Material* material() const { return _material; }

    virtual Geometry*	Clone() const = 0;
    virtual bool Hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

private:
    RGBColor  _color;		// only used for Bare Bones ray tracing (and legacy support for a bit)
    Material* _material;
};

#endif  // GEOMETRY_GEOMETRY_H_
