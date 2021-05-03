#ifndef CAMERAS_PINHOLE_H_
#define CAMERAS_PINHOLE_H_

#include "cameras/camera.h"
#include "utilities/point.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// Pinhole impementation of the Camera object
class Pinhole : public Camera {
  public:
    // Constructors, destructors
    Pinhole(Point3D eye, Vector3D viewDir, Vector3D up, int fov=45);
    Pinhole(Point3D eye, Vector3D viewDir, int fov=45);
    Pinhole(Point3D eye, Point3D lookat, Vector3D up, int fov=45);
    Pinhole(Point3D eye, Point3D lookat, int fov=45);

    // Accessors, mutators
    void fov(int degrees) { _fov = degrees; }
    int fov() const { return _fov; }
    
    void zoom(double z) { _zoom = z; }
    double zoom() const { return _zoom; }

    double ComputePlaneDepth(World& w) const;
    Vector3D RayDirection(const Point3D& p) const;
    void RenderScene(World& w) override;

  private:
    int _fov = 45.0;    // field-of-view in degrees
    double _zoom = 1.0;  // zoom factor
};

#endif  // CAMERAS_PINHOLE_H_
