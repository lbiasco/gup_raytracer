#include "lights/directional.h"

#include "geometry/geometry.h"
#include "world/world.h"

Directional::Directional(Vector3D dir) : Light(), _ls(1.0), _color(1.0), _direction(dir) {};

Vector3D Directional::GetDirection(ShadeRec& sr) {
    return -1 * _direction.Normalized();
}

bool Directional::InShadow(const Ray& ray, const ShadeRec& sr) const {
    double t;
    ShadeRec dummy(sr.w);

    for (Geometry* object : sr.w.objects()) {
        if (object->castsShadows() && object->Hit(ray, t, dummy, true)) {
            return true;
        }
    }

    return false;
}

RGBColor Directional::L(ShadeRec& sr) {
    return (_ls * _color);
}
