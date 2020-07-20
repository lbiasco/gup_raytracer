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
    Pinhole(Point3D eye, Vector3D view_dir, Vector3D up, int fov=45);
    Pinhole(Point3D eye, Vector3D view_dir, int fov=45);
    Pinhole(Point3D eye, Point3D lookat, Vector3D up, int fov=45);
    Pinhole(Point3D eye, Point3D lookat, int fov=45);

    // Accessors, mutators
    void fov(int degrees) { fov_ = degrees; }
    int fov() const { return fov_; }
    
    void zoom(double z) { zoom_ = z; }
    double zoom() const { return zoom_; }

    double ComputePlaneDepth(World& w) const;
    Vector3D RayDirection(const Point3D& p) const;
    void RenderScene(World& w) override;

  private:
    int fov_ = 45.0;    // field-of-view in degrees
    double zoom_ = 1.0;  // zoom factor
};

#endif  // CAMERAS_PINHOLE_H_
