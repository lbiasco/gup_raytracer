#ifndef UTILITIES_SHADE_REC_H_
#define UTILITIES_SHADE_REC_H_

class World;

#include "utilities/point.h"
#include "utilities/normal.h"
#include "utilities/rgb_color.h"

class ShadeRec {
  public:
    ShadeRec(World& wr);
    ShadeRec(const ShadeRec& sr);

    bool      hit_an_object_;   // did the ray hit an object?
    Point3D   local_hit_point_; // world coordinates of hit point 
    Normal    normal_;          // normal at hit point
    RGBColor  color_;           // used in Chapter 3 only
    World&    w_;               // world reference for shading
};

#endif  // UTILITIES_SHADE_REC_H_
