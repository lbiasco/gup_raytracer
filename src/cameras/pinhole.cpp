#include "cameras/pinhole.h"

#include "samplers/sampler.h"
#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

Pinhole::Pinhole(Point3D eye, Point3D lookat, Vector3D up, float d) 
    : Camera(eye, lookat, up), d_(d) {}

Pinhole::Pinhole(Point3D eye, Point3D lookat, float d) 
    : Camera(eye, lookat), d_(d) {}

Pinhole::~Pinhole(void) {}

Vector3D Pinhole::RayDirection(const Point2D& p) const {
  Vector3D dir = p.x_ * u_ + p.y_ * v_ - d_ * w_;
  dir.Normalize();
  return dir;
}

void Pinhole::RenderScene(World& w) {
  RGBColor L;
  ViewPlane vp(w.vp_);
  Ray ray;
  int depth = 0;          // recursion depth
  Point2D sp;             // sample point in [0,1]x[0,1]
  Point2D pp;             // sample point on a pixel

  vp.s_ /= zoom_;
  ray.o_ = eye_;

  for (int r = 0; r < vp.vres_; r++)          // up
    for (int c = 0; c < vp.hres_; c++) {    // across
      L = kBlack;

      for (int j = 0; j < vp.num_samples_; j++) {
        sp = vp.sampler_ptr_->SampleUnitSquare();
        pp.x_ = vp.s_ * (c - 0.5 * vp.hres_ + sp.x_);
        pp.y_ = vp.s_ * (r - 0.5 * vp.vres_ + sp.y_);
        ray.d_ = RayDirection(pp);
        L += w.tracer_ptr_->TraceRay(ray, depth);
      }

      L /= vp.num_samples_;    // Average the colors
      L *= exposure_;
      w.DisplayPixel(r, c, L);
    }
}
