// this file contains the definition of the World class

#include "interfaces/raytracer.h"

#include "world/world.h"
#include "utilities/constants.h"

// geometric objects

#include "geometry/plane.h"
#include "geometry/sphere.h"

// tracers

#include "tracers/single_sphere.h"
#include "tracers/multiple_objects.h"

// utilities

#include "utilities/vector_3d.h"
#include "utilities/point_3d.h"
#include "utilities/normal.h"
#include "utilities/shade_rec.h"
#include "utilities/maths.h"

// build functions

//#include "build_funcs/build_single_sphere.cpp"
#include "build_funcs/build_multiple_objects.cpp"
//#include "build_funcs/build_bb_cover_pic.cpp"


// -------------------------------------------------------------------- default constructor

World::World(void)
	:  	background_color_(kBlack),
		tracer_ptr_(NULL)
{}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	
	if(tracer_ptr_) {
		delete tracer_ptr_;
		tracer_ptr_ = NULL;
	}	
	
	DeleteObjects();	
}


//------------------------------------------------------------------ RenderScene

// This uses orthographic viewing along the zw axis

void 												
World::RenderScene(void) const {

	RGBColor	pixel_color;	 	
	Ray			ray;					
	int 		hres 	= vp_.hres_;
	int 		vres 	= vp_.vres_;
	float		s		= vp_.s_;
	float		zw		= 100;			// hardwired in

	ray.d_ = Vector3D(0, 0, -1);
	
	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c < hres; c++) {	// across 					
			ray.o_ = Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
			pixel_color = tracer_ptr_->TraceRay(ray);
			DisplayPixel(r, c, pixel_color);
		}
    paint_area_->Terminate();
}  


// ------------------------------------------------------------------ Normalize

RGBColor
World::Normalize(const RGBColor& c) const  {
	float max_value = max(c.r_, max(c.g_, c.b_));
	
	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}


// ------------------------------------------------------------------ ClampToColor
// Set color to red if any component is greater than one

RGBColor
World::ClampToColor(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r_ > 1.0 || raw_color.g_ > 1.0 || raw_color.b_ > 1.0) {
		c.r_ = 1.0; c.g_ = 0.0; c.b_ = 0.0;
	}
		
	return (c);
}


// ---------------------------------------------------------------------------DisplayPixel

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


void
World::DisplayPixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp_.show_out_of_gamut_)
		mapped_color = ClampToColor(raw_color);
	else
		mapped_color = Normalize(raw_color);
	
	if (vp_.gamma_ != 1.0)
		mapped_color = mapped_color.Pow(vp_.inv_gamma_);
	
   //have to start from max y coordinate to convert to screen coordinates
   int x = column;
   int y = vp_.vres_ - row - 1;

   paint_area_->SetPixel(x, y, (int)(mapped_color.r_ * 255),
                             (int)(mapped_color.g_ * 255),
                             (int)(mapped_color.b_ * 255));
}



// ----------------------------------------------------------------------------- HitBareBonesObjects

ShadeRec									
World::HitBareBonesObjects(const Ray& ray) {
	ShadeRec	sr(*this); 
	double		t; 			
	float		tmin 			= kHugeValue;
	int 		num_objects 	= objects_.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects_[j]->Hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object_	= true;
			tmin 				= t; 
			sr.color_			= objects_[j]->GetColor(); 
		}
		
	return (sr);   
}


//------------------------------------------------------------------ DeleteObjects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::DeleteObjects(void) {
	int num_objects = objects_.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects_[j];
		objects_[j] = NULL;
	}	
	
	objects_.erase(objects_.begin(), objects_.end());
}
