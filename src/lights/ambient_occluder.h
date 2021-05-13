#ifndef LIGHTS_AMBIENT_OCCLUDER_H_
#define LIGHTS_AMBIENT_OCCLUDER_H_

#include "lights/light.h"
#include "samplers/sampler.h"
#include "utilities/rgb_color.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Ambient light implementation with occlusion
class AmbientOccluder : public Light {
    public:
        // Constructors, destructors
        AmbientOccluder();

        // Accessors, mutators
        void ls(float val) { _ls = val; }
        float ls() const { return _ls; }

        void color(RGBColor val) { _color = val; }
        RGBColor color() const { return _color; }

        void samplerPtr(Sampler* ptr);
        Sampler* samplerPtr() const { return _samplerPtr; }

        void minAmount(float val) { _minAmount = val; }
        float minAmount() const { return _minAmount; }

        // Functions
        virtual Vector3D GetDirection(ShadeRec& sr);
        virtual bool InShadow(const Ray& ray, const ShadeRec& sr) const;
        virtual RGBColor L(ShadeRec& sr);

    private:
        RGBColor    _color;
        float       _ls;
        float    _minAmount;
        Sampler*    _samplerPtr;

        Vector3D _u, _v, _w;
        
};

#endif  // LIGHTS_AMBIENT_OCCLUDER_H_
