#include "lights/ambient_occluder.h"

#include "geometry/geometry.h"
#include "utilities/constants.h"
#include "utilities/ray.h"
#include "world/world.h"

AmbientOccluder::AmbientOccluder() 
    :   Light(), _ls(1.0), _color(1.0), _minAmount(0.0), _samplerPtr(NULL),
        _u(Vector3D(1, 0, 0)), _v(Vector3D(0, 1, 0)), _w(Vector3D(0, 0, 1)) {};

void AmbientOccluder::samplerPtr(Sampler* ptr) {
     if (_samplerPtr) {
        delete _samplerPtr;
        _samplerPtr = NULL;
     }
     _samplerPtr = ptr;
     _samplerPtr->MapSamplesToHemisphere(1);
}

Vector3D AmbientOccluder::GetDirection(ShadeRec& sr) {
    Vector3D sp = _samplerPtr->SampleHemisphere();
    return (sp.x * _u + sp.y * _v + sp.z * _w);
}

bool AmbientOccluder::InShadow(const Ray& ray, const ShadeRec& sr) const {
    double t;
    ShadeRec dummy(sr.w);

    for (Geometry* object : sr.w.objects()) {
        if (object->castsShadows() && object->Hit(ray, t, dummy, true)) {
            return true;
        }
    }
    return false;
}

RGBColor AmbientOccluder::L(ShadeRec& sr) {
    _w = sr.normal;
    // Use jittered up vector if normal is directly up
    _v = (_w == Vector3D(0, 1.0, 0)) ? _w ^ Vector3D(0.001, 1, 0.001) : _w ^ Vector3D(0, 1, 0);
    _v.Normalize();
    _u = _v ^ _w;

    Ray shadowRay(sr.hitPoint, GetDirection(sr));
    if (createsShadows() && InShadow(shadowRay, sr)) {
        return (_minAmount * _ls * _color);
    }
    return (_ls * _color);
}
