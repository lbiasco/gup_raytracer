#include "lights/ambient.h"

Ambient::Ambient() : Light(), _ls(1.0), _color(1.0) {};

Vector3D Ambient::GetDirection(ShadeRec& sr) {
    return (Vector3D(0.0));
}

RGBColor Ambient::L(ShadeRec& sr) {
    return (_ls * _color);
}
