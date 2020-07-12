#include "cameras/pinhole.h"

#include "samplers/sampler.h"
#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

Pinhole::Pinhole(Point3D eye, Point3D lookat, Vector3D up, float d) 
    : Camera(eye, lookat, up), vp_dist_(d) {}

Pinhole::Pinhole(Point3D eye, Point3D lookat, float d) 
    : Camera(eye, lookat), vp_dist_(d) {}

Vector3D Pinhole::RayDirection(const Point2D& p) const {
  Vector3D dir = p.x * u() + p.y * v() - vp_dist_ * w();
  dir.Normalize();
  return dir;
}

void Pinhole::RenderScene(World& w) {
  RGBColor L;
  ViewPlane vp(w.view_plane());
  Ray ray;
  int depth = 0;          // recursion depth
  Point2D sp;             // sample point in [0,1]x[0,1]
  Point2D pp;             // sample point on a pixel

  float s = vp.pixel_scale();
  s /= zoom_;
  vp.pixel_scale(s);
  ray.origin(eye());

  for (int r = 0; r < vp.vres(); r++)          // up
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
