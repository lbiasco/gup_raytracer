#include "cameras/fisheye.h"

#include <tgmath.h>

#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

Fisheye::Fisheye(Point3D eye, Vector3D view_dir, Vector3D up) 
    : Camera(eye, view_dir, up) {}

Fisheye::Fisheye(Point3D eye, Vector3D view_dir) 
    : Camera(eye, view_dir) {}

Fisheye::Fisheye(Point3D eye, Point3D lookat, Vector3D up) 
    : Camera(eye, lookat, up) {}

Fisheye::Fisheye(Point3D eye, Point3D lookat) 
    : Camera(eye, lookat) {}

Vector3D Fisheye::RayDirection(
    const Point2D& pp,
    int hres,
    int vres,
    float s,
    float& r_sq) const {
  // compute the normalized device coordinates
  Point2D pn(2.0 / (s * hres) * pp.x, 2.0 / (s * vres) * pp.y);
  r_sq = pn.x * pn.x + pn.y * pn.y;

  if (r_sq <= 1.0) {
    float r = sqrt(r_sq);
    float psi = r * psi_max_ * kPiOver180;
    float sin_psi = std::sin(psi);
    float cos_psi = std::cos(psi);
    float sin_alpha = pn.y / r;
    float cos_alpha = pn.x / r;
    Vector3D dir = sin_psi * cos_alpha * u() + sin_psi * sin_alpha * v() - cos_psi * w();

    return dir;
  } else
  {
    return Vector3D(0.0);
  }
}


void Fisheye::RenderScene(World& world) {
  RGBColor L;
  ViewPlane vp(world.view_plane());
  double s = vp.pixel_scale();
  Ray ray;
  int depth = 0;  // recursion depth

  Point2D sp;     // sample point in [0,1]x[0,1]
  Point2D pp;     // sample point on a pixel with view plane depth
  float r_sq;     // sum of squares of normalized device coordinates

  ray.origin(eye());

  for (int r = 0; r < vp.vres(); r++)        // up
    for (int c = 0; c < vp.hres(); c++) {    // across
      L = kBlack;

      for (int j = 0; j < vp.num_samples(); j++) {
        sp = vp.sampler_ptr()->SampleUnitSquare();
        pp.x = s * (c - 0.5 * vp.hres() + sp.x);
        pp.y = s * (r - 0.5 * vp.vres() + sp.y);
        ray.dir(RayDirection(pp, vp.hres(), vp.vres(), s, r_sq));

        if (r_sq <= 1.0)
          L += world.tracer_ptr()->TraceRay(ray, depth);
      }

      L /= vp.num_samples();    // Average the colors
      L *= exposure();
      world.DisplayPixel(r, c, L);
    }
}
