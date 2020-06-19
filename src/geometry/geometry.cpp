// this file contains the definition of the class Geometry 

#include "geometry/geometry.h"


// ---------------------------------------------------------------------- default constructor

Geometry::Geometry(void)
	: 	color_(kBlack)
{}


// ---------------------------------------------------------------------- copy constructor

Geometry::Geometry (const Geometry& object)
	: 	color_(object.color_)
{}	


// ---------------------------------------------------------------------- assignment operator

Geometry&														
Geometry::operator= (const Geometry& rhs) {
	
	if (this == &rhs)
		return (*this);
		
	color_ = rhs.color_;

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Geometry::~Geometry (void) {}
