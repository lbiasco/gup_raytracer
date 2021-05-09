#include "lights/point.h"

PointLight::PointLight(Vector3D loc) : Light(), _ls(1.0), _color(1.0), _location(loc), _attenuation(0) {};

Vector3D PointLight::GetDirection(ShadeRec& sr) {
    return (_location - sr.hitPoint).Hat();
}

RGBColor PointLight::L(ShadeRec& sr) {
    if (_attenuation == 0) {
        return (_ls * _color);
    } else {
        return (_ls * _color) / std::pow(std::abs(_location.Distance(sr.hitPoint)), _attenuation);
    }
}
