#include "materials/emissive.h"

#include "lights/light.h"
#include "utilities/constants.h"
#include "utilities/vector.h"
#include "world/world.h"

Emissive::Emissive() : Material(), _ls(1.0), _ce(kWhite) {}
Emissive::Emissive(const Emissive& mat) 
    :   Material(), _ls(mat._ls), _ce(mat._ce) {}
Emissive::Emissive(float ls, RGBColor ce) 
    :   Material(), _ls(ls), _ce(ce) {}

RGBColor Emissive::GetLe() const {
    return _ls * _ce;
}

RGBColor Emissive::AreaLightShade(ShadeRec& sr) {
    if (-sr.normal * sr.ray.dir() > 0.0) {
        return GetLe();
    } else {
        return kBlack;
    }
}

RGBColor Emissive::RayCastShade(ShadeRec& sr) {
    if (-sr.normal * sr.ray.dir() > 0.0) {
        return GetLe();
    } else {
        return kBlack;
    }
}