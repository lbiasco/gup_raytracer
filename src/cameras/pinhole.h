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
    Pinhole(Point3D eye, Point3D lookat, Vector3D up, float d);
    Pinhole(Point3D eye, Point3D lookat, float d);
    ~Pinhole(void) override;

    Vector3D RayDirection(const Point2D& p) const;
    void RenderScene(World& w) override;

  public:
    float d_;           // view-plane distance
    float zoom_ = 1.0;  // zoom factor
};

#endif  // CAMERAS_PINHOLE_H_
