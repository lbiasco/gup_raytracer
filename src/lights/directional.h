#ifndef LIGHTS_DIRECTIONAL_H_
#define LIGHTS_DIRECTIONAL_H_

#include "lights/light.h"
#include "utilities/rgb_color.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Directional light implementation
class Directional : public Light {
    public:
        // Constructors, destructors
        Directional(Vector3D loc);

        // Accessors, mutators
        void ls(float val) { _ls = val; }
        float ls() const { return _ls; }

        void color(RGBColor val) { _color = val; }
        RGBColor color() const { return _color; }

        void direction(Vector3D val) { _direction = val; }
        Vector3D direction() const { return _direction; }

        // Functions
        virtual Vector3D GetDirection(ShadeRec& sr);
        virtual bool InShadow(const Ray& ray, const ShadeRec& sr) const;
        virtual RGBColor L(ShadeRec& sr);

    private:
        float       _ls;
        RGBColor    _color;
        Vector3D    _direction;
};

#endif  // LIGHTS_DIRECTIONAL_H_
