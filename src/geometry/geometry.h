#ifndef GEOMETRY_GEOMETRY_H_
#define GEOMETRY_GEOMETRY_H_

// this file contains the declaration of the class Geometry

#include "utilities/rgb_color.h"
#include "utilities/point_3d.h"
#include "utilities/normal.h"
#include "utilities/ray.h"
#include "utilities/shade_rec.h"
#include "utilities/constants.h"
					

class Geometry {	
	
	public:	

		Geometry(void);				        // default constructor
		
		Geometry(const Geometry& object);	// copy constructor
	
		virtual Geometry*					// virtual copy constructor
		Clone(void) const = 0;

		virtual 							// destructor
		~Geometry (void);	
			
		virtual bool 												 
		Hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
		

		// the following three functions are only required for Chapter 3
		
		void
		SetColor(const RGBColor& c);
				
		void
		SetColor(const float r, const float g, const float b);
		
		RGBColor
		GetColor(void);

	
	protected:
	
		RGBColor   color_;		// only used for Bare Bones ray tracing
	
		Geometry&				// assignment operator
		operator= (const Geometry& rhs);
};


// --------------------------------------------------------------------  SetColor

inline void
Geometry::SetColor(const RGBColor& c) {
	color_ = c;
}

// --------------------------------------------------------------------  SetColor

inline void 
Geometry::SetColor(const float r, const float g, const float b) {
	color_.r_ = r;
	color_.b_ = b;
	color_.g_ = g;
}

// --------------------------------------------------------------------  GetColor

inline RGBColor 
Geometry::GetColor(void) {
	return (color_);
}

#endif  // GEOMETRY_GEOMETRY_H_
