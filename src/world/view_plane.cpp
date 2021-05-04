#include "world/view_plane.h"
	
ViewPlane::ViewPlane(void)							
    :   _hres(400), 
        _vres(400),
        _pixelScale(1.0),
        _numSamples(1),
        _samplerPtr(NULL),
        _gamma(1.0),
        _gammaInv(1.0),
        _showOutOfGamut(false) {}

ViewPlane::ViewPlane(const ViewPlane& vp)   
    :   _hres(vp._hres),  
        _vres(vp._vres), 
        _pixelScale(vp._pixelScale),
        _numSamples(vp._numSamples),
        _samplerPtr(vp._samplerPtr),
        _gamma(vp._gamma),
        _gammaInv(vp._gammaInv),
        _showOutOfGamut(vp._showOutOfGamut) {}

ViewPlane& ViewPlane::operator= (const ViewPlane& rhs) {
    if (this == &rhs)
        return (*this);
        
    _hres         = rhs._hres;
    _vres         = rhs._vres;
    _pixelScale  = rhs._pixelScale;
    _numSamples  = rhs._numSamples;
    _samplerPtr  = rhs._samplerPtr;
    _gamma        = rhs._gamma;
    _gammaInv    = rhs._gammaInv;
    _showOutOfGamut = rhs._showOutOfGamut;

    return *this;
}

void ViewPlane::samplerPtr(Sampler* sp) {
    if (_samplerPtr) {
        delete _samplerPtr;
        _samplerPtr = NULL;
    }

    _numSamples = sp->numSamples();
    _samplerPtr = sp;
}

void ViewPlane::numSamples(int n) {
    _samplerPtr->numSamples(n);
}
