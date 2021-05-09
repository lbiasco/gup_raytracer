#ifndef LIGHTS_AMBIENT_H_
#define LIGHTS_AMBIENT_H_

#include "lights/light.h"
#include "utilities/rgb_color.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Ambient light implementation
class Ambient : public Light {
public:
    // Constructors, destructors
    Ambient();

    // Accessors, mutators
    void ls(float val) { _ls = val; }
    float ls() const { return _ls; }

    void color(RGBColor val) { _color = val; }
    RGBColor color() const { return _color; }

    // Functions
    virtual Vector3D GetDirection(ShadeRec& sr);
    virtual RGBColor L(ShadeRec& sr);

private:
    float       _ls;
    RGBColor    _color;
};

#endif  // LIGHTS_AMBIENT_H_
