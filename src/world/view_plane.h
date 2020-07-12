#ifndef WORLD_VIEW_PLANE_H_
#define WORLD_VIEW_PLANE_H_

#include "samplers/sampler.h"

class ViewPlane {
  public:
    ViewPlane();
    ViewPlane(const ViewPlane& vp);
    ViewPlane& operator= (const ViewPlane& rhs);

    void gamma(float g) { gamma_ = g; inv_gamma_ = 1.0 / gamma_; }
    float gamma() const { return gamma_; }
    float inv_gamma() const { return inv_gamma_; }

    void hres(int w) { hres_ = w; }
    int hres() const { return hres_; }
    void vres(int h) { vres_ = h; }
    int vres() const { return vres_; }

    void num_samples(int n);
    int num_samples() const { return num_samples_; }

    void pixel_scale(float s) { pixel_scale_ = s; }
    float pixel_scale() const { return pixel_scale_; }

    void sampler_ptr(Sampler *ptr);
    Sampler* sampler_ptr() const { return sampler_ptr_; }

    void show_out_of_gamut(bool b) { show_out_of_gamut_ = b; }
    bool show_out_of_gamut() const { return show_out_of_gamut_; }

  private:
    float	gamma_;           // gamma correction factor
    float	inv_gamma_;       // the inverse of the gamma correction factor
    int   hres_;            // horizontal image resolution 
    int   vres_;            // vertical image resolution
    int   num_samples_;     // number of samples per pixel
    float pixel_scale_;     // pixel size
    Sampler *sampler_ptr_;  // pointer to a Sampler object
    bool  show_out_of_gamut_; // display red if RGBColor out of gamut		
};

#endif  // WORLD_VIEW_PLANE_H_
