#ifndef CAMERAS_THIN_LENS_H_
#define CAMERAS_THIN_LENS_H_

#include "cameras/pinhole.h"
#include "samplers/sampler.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// ThinLens impementation of the Camera object
class ThinLens : public Pinhole {
    public:
        // Constructors, destructors
        ThinLens(Vector3D eye, Vector3D viewDir, Vector3D up);
        ThinLens(Vector3D eye, Vector3D viewDir);

        // Accessors, mutators
        void focalLength(double distance) { _focalLength = distance; }
        double focalLength() const { return _focalLength; }

        void lensRadius(double r) { _lensRadius = r; }
        double lensRadius() const { return _lensRadius; }

        void samplerPtr(Sampler* ptr);
        Sampler* samplerPtr() const { return _samplerPtr; }

        Vector3D RayDirection(const Vector3D& pixelPoint, const Vector2D& lensPoint) const;
        void RenderScene(World& w) override;

    private:
        double _focalLength = 10;  // focal plane distance
        double _lensRadius = 1;    // lensRadius
        Sampler* _samplerPtr = NULL;       // sampler object
};

#endif  // CAMERAS_THIN_LENS_H_