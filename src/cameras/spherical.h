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
    Spherical(Point3D eye, Vector3D view_dir, Vector3D up);
    Spherical(Point3D eye, Vector3D view_dir);
    Spherical(Point3D eye, Point3D lookat, Vector3D up);
    Spherical(Point3D eye, Point3D lookat);

    // Accessors, mutators
    double psi_max() const { return psi_max_; }

    Vector3D RayDirection(const Point2D& pp, int hres, int vres, float s) const;
    void RenderScene(World& w) override;
    void SetHFov(double degrees) { lambda_max_ = degrees / 2;}
    void SetVFov(double degrees) { psi_max_ = degrees / 2;}

  private:
    double lambda_max_  = 90; // in degrees
    double psi_max_     = 45; // in degrees
};

#endif  // CAMERAS_SPHERICAL_H_