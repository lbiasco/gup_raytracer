#ifndef LIGHTS_POINT_H_
#define LIGHTS_POINT_H_

#include "lights/light.h"
#include "utilities/rgb_color.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Point light implementation
class PointLight : public Light {
public:
    // Constructors, destructors
    PointLight(Vector3D loc);

    // Accessors, mutators
    void ls(float val) { _ls = val; }
    float ls() const { return _ls; }

    void color(RGBColor val) { _color = val; }
    RGBColor color() const { return _color; }

    void location(Vector3D val) { _location = val; }
    Vector3D location() const { return _location; }

    void attenuation(float val) { _attenuation = val; }
    float attenuation() const { return _attenuation; }

    // Functions
    virtual Vector3D GetDirection(ShadeRec& sr);
    virtual RGBColor L(ShadeRec& sr);

private:
    float       _ls;
    RGBColor    _color;
    Vector3D    _location;
    float       _attenuation;
};

#endif  // LIGHTS_POINT_H_
