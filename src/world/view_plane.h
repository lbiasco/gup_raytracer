#ifndef WORLD_VIEW_PLANE_H_
#define WORLD_VIEW_PLANE_H_

#include "samplers/sampler.h"

class ViewPlane {
    public:
        ViewPlane();
        ViewPlane(const ViewPlane& vp);
        ViewPlane& operator= (const ViewPlane& rhs);

        void gamma(float g) { _gamma = g; _gammaInv = 1.0 / _gamma; }
        float gamma() const { return _gamma; }
        float gammaInv() const { return _gammaInv; }

        void hres(int w) { _hres = w; }
        int hres() const { return _hres; }
        void vres(int h) { _vres = h; }
        int vres() const { return _vres; }

        void numSamples(int n);
        int numSamples() const { return _numSamples; }

        void pixelScale(float s) { _pixelScale = s; }
        float pixelScale() const { return _pixelScale; }

        void samplerPtr(Sampler* ptr);
        Sampler* samplerPtr() const { return _samplerPtr; }

        void showOutOfGamut(bool b) { _showOutOfGamut = b; }
        bool showOutOfGamut() const { return _showOutOfGamut; }

    private:
        float	_gamma;         // gamma correction factor
        float	_gammaInv;      // the inverse of the gamma correction factor
        int     _hres;          // horizontal image resolution 
        int     _vres;          // vertical image resolution
        int     _numSamples;    // number of samples per pixel
        float   _pixelScale;    // pixel size
        Sampler* _samplerPtr;   // pointer to a Sampler object
        bool    _showOutOfGamut; // display red if RGBColor out of gamut		
};

#endif  // WORLD_VIEW_PLANE_H_
