// this file contains the definition of the World class

#include "interfaces/raytracer.h"

#include "world/world.h"
#include "utilities/constants.h"

// brdfs
#include "brdfs/blinn.h"
#include "brdfs/lambertian.h"
#include "brdfs/phong.h"

// cameras
#include "cameras/fisheye.h"
#include "cameras/pinhole.h"
#include "cameras/spherical.h"
#include "cameras/thin_lens.h"

// geometric objects
#include "geometry/plane.h"
#include "geometry/rectangle.h"
#include "geometry/sphere.h"

// lights
#include "lights/ambient.h"
#include "lights/ambient_occluder.h"
#include "lights/directional.h"
#include "lights/point.h"

// materials
#include "materials/glossy.h"
#include "materials/matte.h"
#include "materials/plastic.h"

// sampler
#include "samplers/regular.h"
#include "samplers/hammersley.h"
#include "samplers/jittered.h"
#include "samplers/multi_jittered.h"
#include "samplers/random.h"
#include "samplers/rooks.h"

// tracers
#include "tracers/function.h"
#include "tracers/raycast.h"

// utilities
#include "utilities/vector.h"
#include "utilities/shade_rec.h"
#include "utilities/maths.h"

// build functions
//#include "build_funcs/bb_cover_pic.cpp"
//#include "build_funcs/multiple_objects.cpp"
//#include "build_funcs/sinusoid_func.cpp"
//#include "build_funcs/two_sphere_and_lights.cpp"
//#include "build_funcs/sphere_on_plane.cpp"
#include "build_funcs/rectangle_area_light.cpp"

World::World() 
    :   _ambientPtr(new Ambient), 
        _bgColor(kBlack), 
        _cameraPtr(NULL), 
        _lights(std::vector<Light*>()),
        _objects(std::vector<Geometry*>()),
        _paintArea(NULL),
        _tracerPtr(NULL),
        _viewPlane(ViewPlane()) {}

World::~World() {	
    if(_tracerPtr) {
        delete _tracerPtr;
        _tracerPtr = NULL;
    }
    DeleteObjects();	
}

// Using RenderScene thru World while _cameraPtr targets only a single camera
void World::RenderScene() {
    assert(("No tracer has been set.", _tracerPtr != NULL));

    _cameraPtr->RenderScene(*this);
    _paintArea = NULL;
}

RGBColor World::Normalize(const RGBColor& c) const  {
    float maxValue = std::max(c.r, std::max(c.g, c.b));

    if (maxValue > 1.0)
        return (c / maxValue);
    else
        return c;
}

RGBColor World::ClampToColor(const RGBColor& rawColor) const {
    RGBColor c(rawColor);
    if (rawColor.r > 1.0 || rawColor.g > 1.0 || rawColor.b > 1.0) {
        c.r = 1.0; c.g = 0.0; c.b = 0.0;
    }
    return c;
}

// rawColor is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mappedColor has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function
void World::DisplayPixel(const int row, const int column, const RGBColor& rawColor) const {
    RGBColor mappedColor;

    if (_viewPlane.showOutOfGamut())
        mappedColor = ClampToColor(rawColor);
    else
        mappedColor = Normalize(rawColor);

    if (_viewPlane.gamma() != 1.0)
        mappedColor = mappedColor.Pow(_viewPlane.gammaInv());

        //have to start from max y coordinate to convert to screen coordinates
        int x = column;
        int y = _viewPlane.vres() - row - 1;

        _paintArea->SetPixel(
            x, y, 
            (int)(mappedColor.r * 255),
            (int)(mappedColor.g * 255),
            (int)(mappedColor.b * 255)
        );
}

ShadeRec World::HitObjects(const Ray& ray) {
    ShadeRec  sr(*this); 
    double    t;
    Vector3D  normal;
    Vector3D   localHitPoint;
    float     tmin       = kHugeValue;
    int       numObjects = _objects.size();

    for (int j = 0; j < numObjects; j++) {
        if (_objects[j]->Hit(ray, t, sr) && (t < tmin)) {
            sr.hitAnObject	= true;
            tmin = t; 
            sr.materialPtr = _objects[j]->materialPtr();
            sr.hitPoint = ray.origin() + t * ray.dir();
            normal = sr.normal;
            localHitPoint = sr.localHitPoint;
        }
    }

    if (sr.hitAnObject) {
        sr.normal = normal;
        sr.localHitPoint = localHitPoint;
    }
        
    return (sr);   
}

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 
void World::DeleteObjects() {
    int numObjects = _objects.size();

    for (int j = 0; j < numObjects; j++) {
        delete _objects[j];
        _objects[j] = NULL;
    }
    _objects.erase(_objects.begin(), _objects.end());
}
