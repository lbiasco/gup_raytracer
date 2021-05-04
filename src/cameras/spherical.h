#ifndef CAMERAS_SPHERICAL_H_
#define CAMERAS_SPHERICAL_H_

#include "cameras/camera.h"
#include "utilities/point.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// Spherical impementation of the Camera object
class Spherical : public Camera {
public:
    // Constructors, destructors
    Spherical(Point3D eye, Vector3D viewDir, Vector3D up);
    Spherical(Point3D eye, Vector3D viewDir);
    Spherical(Point3D eye, Point3D lookat, Vector3D up);
    Spherical(Point3D eye, Point3D lookat);

    // Accessors, mutators
    double psiMax() const { return _psiMax; }

    Vector3D RayDirection(const Point2D& pp, int hres, int vres, float s) const;
    void RenderScene(World& w) override;
    void SetHFov(double degrees) { _lambdaMax = degrees / 2;}
    void SetVFov(double degrees) { _psiMax = degrees / 2;}

private:
    double _lambdaMax  = 90; // in degrees
    double _psiMax     = 45; // in degrees
};

#endif  // CAMERAS_SPHERICAL_H_