#include "lights/point.h"

#include "geometry/geometry.h"
#include "world/world.h"

PointLight::PointLight(Vector3D loc) : Light(), _ls(1.0), _color(1.0), _location(loc), _attenuation(0) {};

Vector3D PointLight::GetDirection(ShadeRec& sr) {
    return (_location - sr.hitPoint).Normalized();
}

bool PointLight::InShadow(const Ray& ray, const ShadeRec& sr) const {
    double t;
    float d = _location.Distance(ray.origin());
    ShadeRec dummy(sr.w);

    for (Geometry* object : sr.w.objects()) {
        if (object->castsShadows() && object->Hit(ray, t, dummy, true) && t < d) {
            return true;
        }
    }

    return false;
}

RGBColor PointLight::L(ShadeRec& sr) {
    if (_attenuation == 0) {
        return (_ls * _color);
    } else {
        return (_ls * _color) / std::pow(std::abs(_location.Distance(sr.hitPoint)), _attenuation);
    }
}
