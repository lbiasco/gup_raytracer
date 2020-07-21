#include "cameras/spherical_projection.h"

#include <tgmath.h>

#include "utilities/constants.h"
#include "utilities/matrix.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

SphericalProjection::SphericalProjection(Point3D eye, Vector3D view_dir, Vector3D up) 
    : Camera(eye, view_dir, up) {}

SphericalProjection::SphericalProjection(Point3D eye, Vector3D view_dir) 
    : Camera(eye, view_dir) {}

SphericalProjection::SphericalProjection(Point3D eye, Point3D lookat, Vector3D up) 
    : Camera(eye, lookat, up) {}

SphericalProjection::SphericalProjection(Point3D eye, Point3D lookat) 
    : Camera(eye, lookat) {}

Vector3D SphericalProjection::RayDirection(const Point3D& p) const {
  Vector3D dir = p.x * u() + p.y * v() - p.z * w();
  dir.Normalize();
  return dir;
}

void SphericalProjection::RenderScene(World& w) {
  RGBColor L;
  ViewPlane vp(w.view_plane());
  double s = vp.pixel_scale();
  Ray ray;
  Vector3D outgoing;
  Matrix rotation;
  int depth = 0;          // recursion depth
  Point2D sp;             // sample point in [0,1]x[0,1]

  double increments_theta = 360.0 / (float)vp.hres();
  double increments_iota = 180.0 / (float)vp.vres();
  Vector3D y_vec(0, 1, 0);

  Vector3D x_vec(1, 0, 0);
  Vector3D z_vec(0, 0, 1);

  Vector3D test = Vector3D::RotateAbout(z_vec, x_vec, 180);

  ray.origin(eye());

  for (int r = 0; r < vp.vres(); r++)        // up
    for (int c = 0; c < vp.hres(); c++) {    // across
      L = kBlack;

      for (int j = 0; j < vp.num_samples(); j++) {
        sp = vp.sampler_ptr()->SampleUnitSquare();

        outgoing = Vector3D(sp.x * increments_theta * kPiOver180, sp.y * increments_iota * kPiOver180, 1);
        outgoing.Normalize();
        outgoing = Vector3D::RotateAbout(outgoing, y_vec, (c - vp.hres() * 0.5) * increments_theta);
        outgoing.Normalize();
        Vector3D rotate_about = y_vec ^ outgoing;
        outgoing = Vector3D::RotateAbout(outgoing, rotate_about, (r - vp.vres() * 0.5) * increments_iota);
        outgoing.Normalize();

        ray.dir(RayDirection(Point3D(outgoing.x, outgoing.y, outgoing.z)));
        L += w.tracer_ptr()->TraceRay(ray, depth);
      }

      L /= vp.num_samples();    // Average the colors
      L *= exposure();
      w.DisplayPixel(r, c, L);
    }
}
