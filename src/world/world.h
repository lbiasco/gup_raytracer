#ifndef WORLD_WORLD_H_
#define WORLD_WORLD_H_

// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 

#include <vector>

#include "cameras/camera.h"
#include "geometry/geometry.h"
#include "lights/light.h"
#include "materials/material.h"
#include "tracers/tracer.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"

class RenderWorker; 	// Needed to connect to Qt skeleton

class World {	
public:
    World();
    ~World();

    void ambientPtr(Light* ptr) { _ambientPtr = ptr; }
    Light* ambientPtr() const   { return _ambientPtr; }

    void bgColor(RGBColor color) { _bgColor = color; }
    RGBColor bgColor() const     { return _bgColor; }

    void cameraPtr(Camera* ptr)  { _cameraPtr = ptr; }
    Camera* cameraPtr() const    { return _cameraPtr; }

    void lights(std::vector<Light*> lights) { _lights = lights; }
    std::vector<Light*> lights() const      { return _lights; }

    void objects(std::vector<Geometry*> objs)   { _objects = objs; }
    std::vector<Geometry*> objects() const      { return _objects; }

    void paintArea(RenderWorker* ptr)  { _paintArea = ptr; }
    RenderWorker* paintArea() const    { return _paintArea; }

    void tracerPtr(Tracer* ptr)  { _tracerPtr = ptr; }
    Tracer* tracerPtr() const    { return _tracerPtr; }

    void viewPlane(ViewPlane vp) { _viewPlane = vp; }
    ViewPlane viewPlane() const  { return _viewPlane; }

    void AddLight(Light* lightPtr);
    void AddObject(Geometry* objectPtr);
    void Build();   
    RGBColor ClampToColor(const RGBColor& c) const;
    void DisplayPixel(const int row, const int column, const RGBColor& pixel_color) const;
    ShadeRec HitObjects(const Ray& ray);
    RGBColor Normalize(const RGBColor& c) const;
    void RenderScene();

private:
    Light*        _ambientPtr;
    RGBColor      _bgColor;
    Camera*       _cameraPtr;
    std::vector<Light*> _lights;
    std::vector<Geometry*>  _objects;
    RenderWorker* _paintArea;
    Tracer*       _tracerPtr;
    ViewPlane     _viewPlane;

    void DeleteObjects();
};

inline void World::AddLight(Light* lightPtr) {  
    _lights.push_back(lightPtr);	
}

inline void World::AddObject(Geometry* objectPtr) {  
    _objects.push_back(objectPtr);	
}

#endif  // WORLD_WORLD_H_
