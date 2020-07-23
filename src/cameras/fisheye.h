#ifndef CAMERAS_FISHEYE_H_
#define CAMERAS_FISHEYE_H_

#include "cameras/camera.h"
#include "utilities/point.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// Fisheye impementation of the Camera object
class Fisheye : public Camera {
  public:
    // Constructors, destructors
    Fisheye(Point3D eye, Vector3D view_dir, Vector3D up);
    Fisheye(Point3D eye, Vector3D view_dir);
    Fisheye(Point3D eye, Point3D lookat, Vector3D up);
    Fisheye(Point3D eye, Point3D lookat);

    // Accessors, mutators
    double psi_max() const { return psi_max_; }

    Vector3D RayDirection(const Point2D& pp, int hres, int vres, float s, float& r_sq) const;
    void RenderScene(World& w) override;
    void SetFov(double degrees) { psi_max_ = degrees / 2;}

  private:
    double psi_max_ = 90;  // in degrees
};

#endif  // CAMERAS_FISHEYE_H_