#ifndef GEOMETRY_GEOMETRY_H_
#define GEOMETRY_GEOMETRY_H_

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

    RGBColor color() const { return color_; }
    void color(const RGBColor& c) { color_ = c; }
    void color(const float r, const float g, const float b) { color_ = RGBColor(r, g, b); }

    virtual Geometry*	Clone() const = 0;
    virtual bool Hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

  private:    
    RGBColor  color_;		// only used for Bare Bones ray tracing
};

#endif  // GEOMETRY_GEOMETRY_H_
