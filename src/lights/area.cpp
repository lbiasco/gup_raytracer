#include "lights/area.h"

#include "utilities/constants.h"
#include "world/world.h"

AreaLight::AreaLight(Geometry* obj, Emissive* mat) : Light(), _objectPtr(obj), _materialPtr(mat), _attenuation(0) {};

Vector3D AreaLight::GetDirection(ShadeRec& sr) {
    _samplePoint = _objectPtr->Sample();
    _lightNormal = _objectPtr->GetNormal(_samplePoint);
    Vector3D wi = _samplePoint - sr.hitPoint;
    wi.Normalize();

    return wi;
}

bool AreaLight::InShadow(const Ray& ray, const ShadeRec& sr) const {
    double t;
    float ts = (_samplePoint - ray.origin()) * ray.dir();
    ShadeRec dummy(sr.w);

    for (Geometry* object : sr.w.objects()) {
        if (object->castsShadows() && object->Hit(ray, t, dummy, true) && t < ts) {
            return true;
        }
    }

    return false;
}

RGBColor AreaLight::L(ShadeRec& sr) {
    float ndotd = -_lightNormal * _wi;
    RGBColor l = (ndotd > 0.0) ? _materialPtr->GetLe() : kBlack;
    
    if (_attenuation == 1) {
        return (l / std::pow(std::abs(_samplePoint.Distance(sr.hitPoint)), _attenuation));
    }
    return l;
}

float AreaLight::G(ShadeRec& sr) const {
    float ndotd = -_lightNormal * _wi;
    float d2 = (_samplePoint - sr.hitPoint).LengthSquared();

    return (ndotd / d2);
}

float AreaLight::Pdf(ShadeRec& sr) {
    return _objectPtr->Pdf(sr);
}
