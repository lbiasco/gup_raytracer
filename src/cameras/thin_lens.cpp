#include "cameras/thin_lens.h"

#include <tgmath.h>

#include "samplers/sampler.h"
#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

ThinLens::ThinLens(Point3D eye, Vector3D view_dir, Vector3D up, double f_len, double f_dist) 
    : Camera(eye, view_dir, up), focal_length_(f_len), focal_distance_(f_dist) {}

ThinLens::ThinLens(Point3D eye, Vector3D view_dir, double f_len, double f_dist) 
    : Camera(eye, view_dir), focal_length_(f_len), focal_distance_(f_dist) {}

ThinLens::ThinLens(Point3D eye, Point3D lookat, Vector3D up, double f_len, double f_dist) 
    : Camera(eye, lookat, up), focal_length_(f_len), focal_distance_(f_dist) {}

ThinLens::ThinLens(Point3D eye, Point3D lookat, double f_len, double f_dist) 
    : Camera(eye, lookat), focal_length_(f_len), focal_distance_(f_dist) {}

void ThinLens::RenderScene(World& world) {
  RGBColor L;
  ViewPlane vp(world.view_plane());
  double s = vp.pixel_scale();
  int depth = 0;          // recursion depth
  Point3D sp;             // sample point in [0,1]x[0,1]
  Point3D pp;             // point on a pixel with view plane depth

  Point3D lp;             // point on the lense matching the x, y values of pp
  Point3D intersection;
  Ray thru_center;
  Ray thru_focal;
  
  Ray vp_to_lens;
  Point3D trace_start;
  Ray trace_ray;
  float t;

  Point3D lens_center = eye() + focal_distance_ * w();
  Point3D focal_point = lens_center + focal_length_ * w();

  //int fov = std::max(1, std::min(fov_, 179)); // Lock fov to 1-179 for now
  //double half_width = vp.hres() * s * 0.5; // Multiply by s to maintain fov across resolutions
  //pp.z = half_width / std::tan(fov * 0.5 * kPiOver180);
  //s /= zoom_;
  //ray.origin(eye());

  for (int r = 0; r < vp.vres(); r++)        // up
    for (int c = 0; c < vp.hres(); c++) {    // across
      L = kBlack;

      pp = eye() + s * (c - 0.5 * vp.hres()) * u() + s * (r - 0.5 * vp.vres()) * v();
      thru_center.origin(pp);
      thru_center.dir((lens_center - pp).Hat());

      lp = pp + focal_distance_ * w();
      thru_focal.origin(lp);
      thru_focal.dir((focal_point - lp).Hat());

      intersection = thru_focal.Intersect(thru_center);

      for (int j = 0; j < vp.num_samples(); j++) {
        sp = vp.sampler_ptr()->SampleHemisphere();

        vp_to_lens.origin(pp);
        vp_to_lens.dir((sp.x * u() + sp.y * v() + sp.z * w()).Hat());

        t = focal_distance_ / sp.z;
        trace_start = vp_to_lens.origin() + vp_to_lens.dir() * t;
        trace_ray.origin(trace_start);
        trace_ray.dir((intersection - trace_start).Hat());

        L += world.tracer_ptr()->TraceRay(trace_ray, depth);
      }

      L /= vp.num_samples();    // Average the colors
      L *= exposure();
      world.DisplayPixel(r, c, L);
    }
}
