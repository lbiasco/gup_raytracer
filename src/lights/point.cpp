#include "lights/point.h"

PointLight::PointLight(Vector3D loc) : Light(), _ls(1.0), _color(1.0), _location(loc) {};

Vector3D PointLight::GetDirection(ShadeRec& sr) {
    return (_location - sr.hitPoint).Hat();
}

RGBColor PointLight::L(ShadeRec& sr) {
    return (_ls * _color);
}
