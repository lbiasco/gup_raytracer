#include "lights/ambient.h"

Ambient::Ambient() : Light(), _ls(1.0), _color(1.0) {};

Vector3D Ambient::GetDirection(ShadeRec& sr) {
    return (Vector3D(0.0));
}

bool Ambient::InShadow(const Ray& ray, const ShadeRec& sr) const {
    return false; // Cannot be in shadow for ambient lighting
}

RGBColor Ambient::L(ShadeRec& sr) {
    return (_ls * _color);
}
