#ifndef GEOMETRY_GEOMETRY_H_
#define GEOMETRY_GEOMETRY_H_

#include "utilities/rgb_color.h"
#include "utilities/point.h"
#include "utilities/normal.h"
#include "utilities/ray.h"
#include "utilities/shade_rec.h"
#include "utilities/constants.h"

// Base class for Geometry objects
class Geometry {	
  public:
    // Constructors, destructors
    Geometry(void);
    Geometry(const Geometry& object);
    virtual ~Geometry (void);	

    RGBColor GetColor(void);
    void SetColor(const RGBColor& c);
    void SetColor(const float r, const float g, const float b);

    virtual Geometry*	Clone(void) const = 0;
    virtual bool Hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

  protected:
    Geometry&	operator= (const Geometry& rhs);
    
    RGBColor  color_;		// only used for Bare Bones ray tracing
};

// Inline functions

inline RGBColor Geometry::GetColor(void) {
  return (color_);
}

inline void Geometry::SetColor(const RGBColor& c) {
  color_ = c;
}

inline void Geometry::SetColor(const float r, const float g, const float b) {
  color_.r_ = r;
  color_.b_ = b;
  color_.g_ = g;
}

#endif  // GEOMETRY_GEOMETRY_H_
