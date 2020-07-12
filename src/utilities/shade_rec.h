#ifndef UTILITIES_SHADE_REC_H_
#define UTILITIES_SHADE_REC_H_

#include "utilities/point.h"
#include "utilities/rgb_color.h"
#include "utilities/vector.h"

class World;

struct ShadeRec {
    ShadeRec(World& wr);
    ShadeRec(const ShadeRec& sr);

    bool      hit_an_object;   // did the ray hit an object?
    Point3D   local_hit_point; // world coordinates of hit point 
    Vector3D  normal;          // normal at hit point
    RGBColor  color;           // used in Chapter 3 only
    World&    w;               // world reference for shading
};

#endif  // UTILITIES_SHADE_REC_H_
