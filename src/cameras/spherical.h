#ifndef CAMERAS_SPHERICAL_H_
#define CAMERAS_SPHERICAL_H_

#include "cameras/camera.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// Spherical impementation of the Camera object
class Spherical : public Camera {
    public:
        // Constructors, destructors
        Spherical(Vector3D eye, Vector3D viewDir, Vector3D up);
        Spherical(Vector3D eye, Vector3D viewDir);

        // Accessors, mutators
        double psiMax() const { return _psiMax; }

        Vector3D RayDirection(const Vector2D& pp, int hres, int vres, float s) const;
        void RenderScene(World& w) override;
        void SetHFov(double degrees) { _lambdaMax = degrees / 2;}
        void SetVFov(double degrees) { _psiMax = degrees / 2;}

    private:
        double _lambdaMax  = 90; // in degrees
        double _psiMax     = 45; // in degrees
};

#endif  // CAMERAS_SPHERICAL_H_