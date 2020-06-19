#ifndef UTILITIES_SHADE_REC_H_
#define UTILITIES_SHADE_REC_H_

// this file contains the declaration of the class ShadeRec

class World;	// only need a forward class declaration as the World data member is a reference

#include "utilities/point_3d.h"
#include "utilities/normal.h"
#include "utilities/rgb_color.h"

class ShadeRec {
	public:
	
		bool				hit_an_object_;		// did the ray hit an object?
		Point3D				local_hit_point_;	// world coordinates of hit point 
		Normal				normal_;				// normal at hit point
		RGBColor			color_;				// used in Chapter 3 only
		World&				w_;					// world reference for shading
				
		ShadeRec(World& wr);				// constructor
		
		ShadeRec(const ShadeRec& sr);		// copy constructor
};

#endif  // UTILITIES_SHADE_REC_H_
