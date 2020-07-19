#ifndef CAMERAS_THIN_LENS_H_
#define CAMERAS_THIN_LENS_H_

#include "cameras/camera.h"
#include "utilities/point.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// ThinLens impementation of the Camera object
class ThinLens : public Camera {
  public:
    // Constructors, destructors
    ThinLens(Point3D eye, Vector3D view_dir, Vector3D up, double f_len=1, double f_dist=1);
    ThinLens(Point3D eye, Vector3D view_dir, double f_len=1, double f_dist=1);
    ThinLens(Point3D eye, Point3D lookat, Vector3D up, double f_len=1, double f_dist=1);
    ThinLens(Point3D eye, Point3D lookat, double f_len=1, double f_dist=1);

    // Accessors, mutators
    void focal_length(double distance) { focal_length_ = distance; }
    double focal_length() const { return focal_length_; }

    void focal_distance(double distance) { focal_distance_ = distance; }
    double focal_distance() const { return focal_distance_; }

    void RenderScene(World& w) override;

  private:
    double focal_length_ = 1.0;    // field-of-view in degrees
    double focal_distance_ = 1.0;  // zoom factor
};

#endif  // CAMERAS_THIN_LENS_H_
