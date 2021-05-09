#ifndef UTILITIES_SHADE_REC_H_
#define UTILITIES_SHADE_REC_H_

#include "utilities/point.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "utilities/vector.h"

// Forward declarations
class Material;
class World;

struct ShadeRec {
    ShadeRec(World& wr);
    ShadeRec(const ShadeRec& sr);

    bool        hitAnObject;    // did the ray hit an object?
    Material*   materialPtr;    // nearest object's material
    Point3D     hitPoint;       // world coordinates of hit point
    Point3D     localHitPoint;  // for attaching textures to objects 
    Vector3D    normal;         // normal at hit point
    RGBColor    color;          // used in Chapter 3 only
    Ray         ray;            // for specular highlights
    int         depth;          // for recursion depth
    Vector3D    dir;            // for area lights
    World&      w;              // world reference for shading
};

#endif  // UTILITIES_SHADE_REC_H_
