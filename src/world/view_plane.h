#ifndef WORLD_VIEW_PLANE_H_
#define WORLD_VIEW_PLANE_H_

//-------------------------------------------------------------------------------------- class ViewPlane

class ViewPlane {
	public:
		int 	hres_;   					// horizontal image resolution 
		int 	vres_;   					// vertical image resolution
		float	s_;							// pixel size
        int     num_samples_;               // number of samples per pixel
		
		float	gamma_;						// gamma correction factor
		float	inv_gamma_;					// the inverse of the gamma correction factor
		bool    show_out_of_gamut_;			// display red if RGBColor out of gamut
		
									
	
	public:
	
		ViewPlane();   								// default Constructor
				
		ViewPlane(const ViewPlane& vp);				// copy constructor

		ViewPlane& operator= (const ViewPlane& rhs);		// assignment operator
		
		~ViewPlane();   							// destructor
						
		void 													
		SetHRes(const int h_res);
		
		void 													
		SetVRes(const int v_res);
				
		void
		SetPixelSize(const float size);

        void
        SetSamples(const int samples);
		
		void
		SetGamma(const float g);
		
		void
		SetGamutDisplay(const bool show);				
};




// ------------------------------------------------------------------------------ SetHRes

inline void 													
ViewPlane::SetHRes(const int h_res) {
	hres_ = h_res;
}


// ------------------------------------------------------------------------------ SetVRes

inline void 													
ViewPlane::SetVRes(const int v_res) {
	vres_ = v_res;
}


// ------------------------------------------------------------------------------ SetPixelSize

inline void 													
ViewPlane::SetPixelSize(const float size) {
	s_ = size;
}


// ------------------------------------------------------------------------------ SetPixelSize

inline void 													
ViewPlane::SetSamples(const int samples) {
	num_samples_ = samples;
}


// ------------------------------------------------------------------------------ SetGamma

inline void
ViewPlane::SetGamma(const float g) {
	gamma_ = g;
	inv_gamma_ = 1.0 / gamma_;
}


// ------------------------------------------------------------------------------ SetGamutDisplay

inline void
ViewPlane::SetGamutDisplay(const bool show) {
	show_out_of_gamut_ = show;
}


#endif  // WORLD_VIEW_PLANE_H_
