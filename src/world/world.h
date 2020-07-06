#ifndef WORLD_WORLD_H_
#define WORLD_WORLD_H_

// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 

#include <vector>

#include "cameras/camera.h"
#include "geometry/geometry.h"
#include "geometry/sphere.h"
#include "tracers/tracer.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"

class RenderWorker; 	// Needed to connect to Qt skeleton


class World {	
	public:
        Camera*             camera_ptr_;
		ViewPlane			vp_;
		RGBColor			background_color_;
		Tracer*				tracer_ptr_;
		std::vector<Geometry*>   objects_;		
		RenderWorker* 		paint_area_;

	public:
	
		World(void);												
		
		~World();
								
		void 
		AddObject(Geometry* object_ptr);
		
		void 					
		Build(void);

		void 												
		RenderScene(void);
						
		RGBColor
		Normalize(const RGBColor& c) const;
		
		RGBColor
		ClampToColor(const RGBColor& c) const;
		
		void
		DisplayPixel(const int row, const int column, const RGBColor& pixel_color) const;

		ShadeRec									
		HitBareBonesObjects(const Ray& ray);
						
	private:
		
		void 
		DeleteObjects(void);

};


// ------------------------------------------------------------------ add_object

inline void 
World::AddObject(Geometry* object_ptr) {  
	objects_.push_back(object_ptr);	
}

#endif  // WORLD_WORLD_H_
