#ifndef CAMERAS_THIN_LENS_H_
#define CAMERAS_THIN_LENS_H_

#include "cameras/pinhole.h"
#include "samplers/sampler.h"
#include "utilities/point.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// ThinLens impementation of the Camera object
class ThinLens : public Pinhole {
public:
    // Constructors, destructors
    ThinLens(Point3D eye, Vector3D viewDir, Vector3D up);
    ThinLens(Point3D eye, Vector3D viewDir);
    ThinLens(Point3D eye, Point3D lookat, Vector3D up);
    ThinLens(Point3D eye, Point3D lookat);

    // Accessors, mutators
    void focalLength(double distance) { _focalLength = distance; }
    double focalLength() const { return _focalLength; }

    void lensRadius(double r) { _lensRadius = r; }
    double lensRadius() const { return _lensRadius; }

    void samplerPtr(Sampler* ptr);
    Sampler* samplerPtr() const { return _samplerPtr; }

    Vector3D RayDirection(const Point3D& pixelPoint, const Point2D& lensPoint) const;
    void RenderScene(World& w) override;

private:
    double _focalLength = 10;  // focal plane distance
    double _lensRadius = 1;    // lensRadius
    Sampler* _samplerPtr = NULL;       // sampler object
};

#endif  // CAMERAS_THIN_LENS_H_