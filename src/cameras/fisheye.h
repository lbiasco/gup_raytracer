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
    Fisheye(Point3D eye, Vector3D viewDir, Vector3D up);
    Fisheye(Point3D eye, Vector3D viewDir);
    Fisheye(Point3D eye, Point3D lookat, Vector3D up);
    Fisheye(Point3D eye, Point3D lookat);

    // Accessors, mutators
    double psiMax() const { return _psiMax; }

    Vector3D RayDirection(const Point2D& pp, int hres, int vres, float s, float& rSq) const;
    void RenderScene(World& w) override;
    void SetFov(double degrees) { _psiMax = degrees / 2;}

  private:
    double _psiMax = 90;  // in degrees
};

#endif  // CAMERAS_FISHEYE_H_