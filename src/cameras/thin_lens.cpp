#include "cameras/thin_lens.h"

#include <tgmath.h>

#include "samplers/sampler.h"
#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

ThinLens::ThinLens(Point3D eye, Vector3D view_dir, Vector3D up) 
    : Pinhole(eye, view_dir, up) {}

ThinLens::ThinLens(Point3D eye, Vector3D view_dir) 
    : Pinhole(eye, view_dir) {}

ThinLens::ThinLens(Point3D eye, Point3D lookat, Vector3D up) 
    : Pinhole(eye, lookat, up) {}

ThinLens::ThinLens(Point3D eye, Point3D lookat) 
    : Pinhole(eye, lookat) {}

void ThinLens::sampler_ptr(Sampler *sp) {
  if (sampler_ptr_) {
    delete sampler_ptr_;
    sampler_ptr_ = NULL;
  }
  sampler_ptr_ = sp;
  sampler_ptr_->MapSamplesToUnitDisk();
}

Vector3D ThinLens::RayDirection(
  const Point3D& pixel_point,
  const Point2D& lens_point) const {
      Point2D p;  // hit point on focal plane
      p.x = pixel_point.x * focal_length_ / pixel_point.z;
      p.y = pixel_point.y * focal_length_ / pixel_point.z;

      Vector3D dir = (p.x - lens_point.x) * u() + 
                    (p.y - lens_point.y) * v() - focal_length_ * w();
      dir.Normalize();
      return dir;
}

void ThinLens::RenderScene(World& world) {
  RGBColor L;
  ViewPlane vp(world.view_plane());
  double s = vp.pixel_scale();
  Ray ray;
  int depth = 0;  // recursion depth

  Point2D sp;     // sample point in [0,1]x[0,1]
  Point3D pp;     // sample point on a pixel with view plane depth
  Point2D dp;     // sample point on unit disk
  Point2D lp;     // sample point on lens

  pp.z = ComputePlaneDepth(world);
  s /= zoom();

  for (int r = 0; r < vp.vres(); r++)        // up
    for (int c = 0; c < vp.hres(); c++) {    // across
      L = kBlack;

      for (int j = 0; j < vp.num_samples(); j++) {
        sp = vp.sampler_ptr()->SampleUnitSquare();
        pp.x = s * (c - 0.5 * vp.hres() + sp.x);
        pp.y = s * (r - 0.5 * vp.vres() + sp.y);

        dp = sampler_ptr_->SampleUnitDisk();
        lp = dp * lens_radius_;

        ray.origin(eye() + lp.x * u() + lp.y * v());
        ray.dir(RayDirection(pp, lp));
        L += world.tracer_ptr()->TraceRay(ray, depth);
      }

      L /= vp.num_samples();    // Average the colors
      L *= exposure();
      world.DisplayPixel(r, c, L);
    }
}
