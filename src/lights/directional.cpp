#include "lights/directional.h"

Directional::Directional(Vector3D dir) : Light(), _ls(1.0), _color(1.0), _direction(dir) {};

Vector3D Directional::GetDirection(ShadeRec& sr) {
    return -1 * _direction.Normalized();
}

RGBColor Directional::L(ShadeRec& sr) {
    return (_ls * _color);
}
