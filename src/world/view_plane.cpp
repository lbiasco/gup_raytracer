// This file contains the definition the ViewPlane class

#include "world/view_plane.h"
	
// ---------------------------------------------------------------- default constructor	
						
ViewPlane::ViewPlane(void)							
	: 	hres_(400), 
		vres_(400),
		s_(1.0),
        num_samples_(1),
        sampler_ptr_(NULL),
		gamma_(1.0),
		inv_gamma_(1.0),
		show_out_of_gamut_(false)
{}


// ---------------------------------------------------------------- copy constructor

ViewPlane::ViewPlane(const ViewPlane& vp)   
	:  	hres_(vp.hres_),  
		vres_(vp.vres_), 
		s_(vp.s_),
        num_samples_(vp.num_samples_),
        sampler_ptr_(vp.sampler_ptr_),
		gamma_(vp.gamma_),
		inv_gamma_(vp.inv_gamma_),
		show_out_of_gamut_(vp.show_out_of_gamut_)
{}


// ---------------------------------------------------------------- assignment operator

ViewPlane& 
ViewPlane::operator= (const ViewPlane& rhs) {
	if (this == &rhs)
		return (*this);
		
	hres_ 				= rhs.hres_;
	vres_ 				= rhs.vres_;
	s_					= rhs.s_;
    num_samples_        = rhs.num_samples_;
    sampler_ptr_        = rhs.sampler_ptr_;
	gamma_				= rhs.gamma_;
	inv_gamma_			= rhs.inv_gamma_;
	show_out_of_gamut_	= rhs.show_out_of_gamut_;
	
	return (*this);
}


// -------------------------------------------------------------- destructor

ViewPlane::~ViewPlane(void) {}

void
ViewPlane::SetSampler(Sampler *sp) {
    if (sampler_ptr_) {
        delete sampler_ptr_;
        sampler_ptr_ = NULL;
    }

    num_samples_ = sp->GetNumSamples();
    sampler_ptr_ = sp;
}

void
ViewPlane::SetNumSamples(const int n) {
    sampler_ptr_->SetNumSamples(n);
}

