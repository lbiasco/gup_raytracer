// this file contains the definition of the class ShadeRec

// there is no default constructor as the World reference always has to be initialised
// there is also no assignment operator as we don't want to assign the world
// the copy constructor only copies the world reference
// the ray tracer is written so that new ShadeRec objects are always constructed
// using the first constructor or the copy constructor

#include "utilities/constants.h"
#include "utilities/shade_rec.h"

// ------------------------------------------------------------------ constructor

ShadeRec::ShadeRec(World& wr)
	: 	hit_an_object_(false),
		local_hit_point_(),
		normal_(),
		color_(kBlack),
		w_(wr)
{}


// ------------------------------------------------------------------ copy constructor

ShadeRec::ShadeRec(const ShadeRec& sr)
	: 	hit_an_object_(sr.hit_an_object_),
		local_hit_point_(sr.local_hit_point_),
		color_(sr.color_),
		w_(sr.w_)
{}
