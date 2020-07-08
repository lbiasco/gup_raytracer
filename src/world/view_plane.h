#ifndef WORLD_VIEW_PLANE_H_
#define WORLD_VIEW_PLANE_H_

#include "samplers/sampler.h"

class ViewPlane {
  public:
    ViewPlane();
    ViewPlane(const ViewPlane& vp);
    ViewPlane& operator= (const ViewPlane& rhs);
    ~ViewPlane();

    void SetHRes(const int h_res);
    void SetVRes(const int v_res);  
    void SetPixelSize(const float size);
    void SetNumSamples(const int n);
    void SetSampler(Sampler *sp);
    void SetGamma(const float g);
    void SetGamutDisplay(const bool show);

    int   hres_;            // horizontal image resolution 
    int   vres_;            // vertical image resolution
    float s_;               // pixel size
    int   num_samples_;     // number of samples per pixel
    Sampler *sampler_ptr_;  // pointer to a Sampler object
    float	gamma_;           // gamma correction factor
    float	inv_gamma_;       // the inverse of the gamma correction factor
    bool  show_out_of_gamut_; // display red if RGBColor out of gamut		
};

// Inline member functions

inline void ViewPlane::SetHRes(const int h_res) {
  hres_ = h_res;
}

inline void ViewPlane::SetVRes(const int v_res) {
  vres_ = v_res;
}

inline void ViewPlane::SetPixelSize(const float size) {
  s_ = size;
}

inline void ViewPlane::SetGamma(const float g) {
  gamma_ = g;
  inv_gamma_ = 1.0 / gamma_;
}

inline void ViewPlane::SetGamutDisplay(const bool show) {
  show_out_of_gamut_ = show;
}

#endif  // WORLD_VIEW_PLANE_H_
