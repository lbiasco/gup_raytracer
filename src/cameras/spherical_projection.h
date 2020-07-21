#ifndef CAMERAS_SPHERICAL_PROJECTION_H_
#define CAMERAS_SPHERICAL_PROJECTION_H_

#include "cameras/camera.h"
#include "utilities/point.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// SphericalProjection impementation of the Camera object
class SphericalProjection : public Camera {
  public:
    // Constructors, destructors
    SphericalProjection(Point3D eye, Vector3D view_dir, Vector3D up);
    SphericalProjection(Point3D eye, Vector3D view_dir);
    SphericalProjection(Point3D eye, Point3D lookat, Vector3D up);
    SphericalProjection(Point3D eye, Point3D lookat);

    Vector3D RayDirection(const Point3D& p) const;
    void RenderScene(World& w) override;
};

#endif  // CAMERAS_SPHERICAL_PROJECTION_H_
