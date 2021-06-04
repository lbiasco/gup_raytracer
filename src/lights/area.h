#ifndef LIGHTS_AREA_H_
#define LIGHTS_AREA_H_

#include "geometry/geometry.h"
#include "lights/light.h"
#include "materials/emissive.h"
#include "utilities/rgb_color.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Area light implementation
class AreaLight : public Light {
    public:
        // Constructors, destructors
        AreaLight(Geometry* obj, Emissive* mat);

        // Accessors, mutators
        void attenuation(float val) { _attenuation = val; }
        float attenuation() const { return _attenuation; }
        
        void objectPtr(Geometry* ptr) { _objectPtr = ptr; }
        Geometry* objectPtr() const { return _objectPtr; }

        void materialPtr(Emissive* ptr) { _materialPtr = ptr; }
        Material* materialPtr() const { return _materialPtr; }

        // Functions
        virtual Vector3D GetDirection(ShadeRec& sr);
        virtual bool InShadow(const Ray& ray, const ShadeRec& sr) const;
        virtual RGBColor L(ShadeRec& sr);
        virtual float G(ShadeRec& sr) const;
        virtual float Pdf(ShadeRec& sr);

    private:
        float _attenuation;
        Geometry* _objectPtr;
        Emissive* _materialPtr;

        Vector3D _samplePoint;          // sample point on the surface
        Vector3D _lightNormal;          // normal at sample point
        Vector3D _wi;                   // unit vector from hit point to sample point
};

#endif  // LIGHTS_AREA_H_
