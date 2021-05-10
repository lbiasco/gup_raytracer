#ifndef CAMERAS_PINHOLE_H_
#define CAMERAS_PINHOLE_H_

#include "cameras/camera.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// Pinhole impementation of the Camera object
class Pinhole : public Camera {
    public:
        // Constructors, destructors
        Pinhole(Vector3D eye, Vector3D viewDir, Vector3D up, int fov=45);
        Pinhole(Vector3D eye, Vector3D viewDir, int fov=45);

        // Accessors, mutators
        void fov(int degrees) { _fov = degrees; }
        int fov() const { return _fov; }
        
        void zoom(double z) { _zoom = z; }
        double zoom() const { return _zoom; }

        void apertureOffsetX(double x) { _apertureOffsetX = x; }
        double apertureOffsetX() { return _apertureOffsetX; }
        
        void apertureOffsetY(double y) { _apertureOffsetY = y; }
        double apertureOffsetY() { return _apertureOffsetY; }

        double ComputePlaneDepth(World& world) const;
        Vector3D RayDirection(const Vector3D& p) const;
        void RenderScene(World& w) override;

    private:
        int _fov = 45.0;    // field-of-view in degrees
        double _zoom = 1.0;  // zoom factor

        double _apertureOffsetX = 0.0;  // aperture variables required for stereo
        double _apertureOffsetY = 0.0;
};

#endif  // CAMERAS_PINHOLE_H_
