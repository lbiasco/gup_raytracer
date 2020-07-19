#include "cameras/pinhole.h"

#include <tgmath.h>

#include "samplers/sampler.h"
#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

Pinhole::Pinhole(Point3D eye, Vector3D view_dir, Vector3D up, int fov) 
    : Camera(eye, view_dir, up), fov_(fov) {}

Pinhole::Pinhole(Point3D eye, Vector3D view_dir, int fov) 
    : Camera(eye, view_dir), fov_(fov) {}

Pinhole::Pinhole(Point3D eye, Point3D lookat, Vector3D up, int fov) 
    : Camera(eye, lookat, up), fov_(fov) {}

Pinhole::Pinhole(Point3D eye, Point3D lookat, int fov) 
    : Camera(eye, lookat), fov_(fov) {}

Vector3D Pinhole::RayDirection(const Point3D& p) const {
  Vector3D dir = p.x * u() + p.y * v() + p.z * w();
  dir.Normalize();
  return dir;
}

void Pinhole::RenderScene(World& w) {
  RGBColor L;
  ViewPlane vp(w.view_plane());
  double s = vp.pixel_scale();
  Ray ray;
  int depth = 0;          // recursion depth
  Point2D sp;             // sample point in [0,1]x[0,1]
  Point3D pp;             // sample point on a pixel with view plane depth

  int fov = std::max(1, std::min(fov_, 179)); // Lock fov to 1-179 for now
  double half_width = vp.hres() * s * 0.5; // Multiply by s to maintain fov across resolutions
  pp.z = half_width / std::tan(fov * 0.5 * kPiOver180);
  s /= zoom_;
  ray.origin(eye());

  for (int r = 0; r < vp.vres(); r++)        // up
    for (int c = 0; c < vp.hres(); c++) {    // across
      L = kBlack;

      for (int j = 0; j < vp.num_samples(); j++) {
        sp = vp.sampler_ptr()->SampleUnitSquare();
        pp.x = s * (c - 0.5 * vp.hres() + sp.x);
        pp.y = s * (r - 0.5 * vp.vres() + sp.y);
        ray.dir(RayDirection(pp));
        L += w.tracer_ptr()->TraceRay(ray, depth);
      }

      L /= vp.num_samples();    // Average the colors
      L *= exposure();
      w.DisplayPixel(r, c, L);
    }
}
