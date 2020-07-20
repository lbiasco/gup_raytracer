#ifndef CAMERAS_THIN_LENS_H_
#define CAMERAS_THIN_LENS_H_

#include "cameras/pinhole.h"
#include "samplers/sampler.h"
#include "utilities/point.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// ThinLens impementation of the Camera object
class ThinLens : public Pinhole {
  public:
    // Constructors, destructors
    ThinLens(Point3D eye, Vector3D view_dir, Vector3D up);
    ThinLens(Point3D eye, Vector3D view_dir);
    ThinLens(Point3D eye, Point3D lookat, Vector3D up);
    ThinLens(Point3D eye, Point3D lookat);

    // Accessors, mutators
    void focal_length(double distance) { focal_length_ = distance; }
    double focal_length() const { return focal_length_; }

    void lens_radius(double r) { lens_radius_ = r; }
    double lens_radius() const { return lens_radius_; }

    void sampler_ptr(Sampler *ptr);
    Sampler* sampler_ptr() const { return sampler_ptr_; }

    Vector3D RayDirection(const Point3D& pixel_point, const Point2D& lens_point) const;
    void RenderScene(World& w) override;

  private:
    double focal_length_ = 10;  // focal plane distance
    double lens_radius_ = 1;    // lens_radius
    Sampler *sampler_ptr_ = NULL;       // sampler object
};

#endif  // CAMERAS_THIN_LENS_H_