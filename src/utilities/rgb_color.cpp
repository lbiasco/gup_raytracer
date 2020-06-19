// This file contains the definition of the class RGBColor

#include <math.h>

#include "utilities/rgb_color.h"

// -------------------------------------------------------- default constructor

RGBColor::RGBColor(void)
	: r_(0.0), g_(0.0), b_(0.0) 							
{}


// -------------------------------------------------------- constructor

RGBColor::RGBColor(float c)
	: r_(c), g_(c), b_(c) 							
{}
								

// -------------------------------------------------------- constructor

RGBColor::RGBColor(float r, float g, float b)	
	: r_(r), g_(g), b_(b)
{}


// -------------------------------------------------------- copy constructor

RGBColor::RGBColor(const RGBColor& c)
	: r_(c.r_), g_(c.g_), b_(c.b_)
{} 				 
		

// -------------------------------------------------------- destructor

RGBColor::~RGBColor(void)		
{}


// --------------------------------------------------------assignment operator

RGBColor& 											
RGBColor::operator= (const RGBColor& rhs) {
	if (this == &rhs)
		return (*this);

	r_ = rhs.r_; g_ = rhs.g_; b_ = rhs.b_;

	return (*this);
}
 

// -------------------------------------------------------- Pow
// raise each component to the specified power
// used for color filtering in Chapter 28

RGBColor
RGBColor::Pow(float p) const {
	return (RGBColor(pow(r_, p), pow(g_, p), pow(b_, p)));
}

