// this file contains the definition of the World class

#include "interfaces/raytracer.h"

#include "world/world.h"
#include "utilities/constants.h"

// cameras
#include "cameras/fisheye.h"
#include "cameras/pinhole.h"
#include "cameras/thin_lens.h"

// geometric objects
#include "geometry/plane.h"
#include "geometry/sphere.h"

// sampler
#include "samplers/regular.h"
#include "samplers/jittered.h"
#include "samplers/rooks.h"
#include "samplers/multi_jittered.h"
#include "samplers/hammersley.h"

// tracers
#include "tracers/multiple_objects.h"
#include "tracers/function.h"

// utilities
#include "utilities/vector.h"
#include "utilities/point.h"
#include "utilities/shade_rec.h"
#include "utilities/maths.h"

// build functions
//#include "build_funcs/build_single_sphere.cpp"
//#include "build_funcs/build_double_sphere.cpp"
//#include "build_funcs/build_single_plane.cpp"
#include "build_funcs/build_multiple_objects.cpp"
//#include "build_funcs/build_bb_cover_pic.cpp"
//#include "build_funcs/build_sinusoid_func.cpp"

World::World() : bg_color_(kBlack), tracer_ptr_(NULL) {}

World::~World() {	
  if(tracer_ptr_) {
    delete tracer_ptr_;
    tracer_ptr_ = NULL;
  }
  DeleteObjects();	
}

// Using RenderScene thru World while camera_ptr_ targets only a single camera
void World::RenderScene() {
  camera_ptr_->RenderScene(*this);
  paint_area_->Terminate();
}

RGBColor World::Normalize(const RGBColor& c) const  {
  float max_value = std::max(c.r, std::max(c.g, c.b));

  if (max_value > 1.0)
    return (c / max_value);
  else
    return c;
}

RGBColor World::ClampToColor(const RGBColor& raw_color) const {
  RGBColor c(raw_color);
  if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
    c.r = 1.0; c.g = 0.0; c.b = 0.0;
  }
  return c;
}

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function
void World::DisplayPixel(const int row, const int column, const RGBColor& raw_color) const {
  RGBColor mapped_color;

  if (view_plane_.show_out_of_gamut())
    mapped_color = ClampToColor(raw_color);
  else
    mapped_color = Normalize(raw_color);

  if (view_plane_.gamma() != 1.0)
    mapped_color = mapped_color.Pow(view_plane_.inv_gamma());

    //have to start from max y coordinate to convert to screen coordinates
    int x = column;
    int y = view_plane_.vres() - row - 1;

    paint_area_->SetPixel(x, y, (int)(mapped_color.r * 255),
                              (int)(mapped_color.g * 255),
                              (int)(mapped_color.b * 255));
}

ShadeRec World::HitBareBonesObjects(const Ray& ray) {
  ShadeRec  sr(*this); 
  double    t;
  float     tmin          = kHugeValue;
  int       num_objects   = objects_.size();

  for (int j = 0; j < num_objects; j++)
    if (objects_[j]->Hit(ray, t, sr) && (t < tmin)) {
      sr.hit_an_object	= true;
      tmin = t; 
      sr.color = objects_[j]->color(); 
    }
    
  return (sr);   
}

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 
void World::DeleteObjects() {
  int num_objects = objects_.size();

  for (int j = 0; j < num_objects; j++) {
    delete objects_[j];
    objects_[j] = NULL;
  }
  objects_.erase(objects_.begin(), objects_.end());
}
