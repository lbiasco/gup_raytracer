#ifndef UTILITIES_RGB_COLOR_H_
#define UTILITIES_RGB_COLOR_H_

#include <math.h>

struct RGBColor {
    float	r, g, b;

    RGBColor() : r(0.0), g(0.0), b(0.0) {}
    RGBColor(float c) : r(c), g(c), b(c) {}
    RGBColor(float a, float b, float c) : r(a), g(b), b(c) {}
    RGBColor(const RGBColor& c) : r(c.r), g(c.g), b(c.b) {}

    RGBColor&  operator= (const RGBColor& rhs); 
    RGBColor operator+ (const RGBColor& c) const { return RGBColor(r + c.r, g + c.g, b + c.b); }
    RGBColor& operator+= (const RGBColor& c);
    RGBColor operator* (const float a) const { return RGBColor(r * a, g * a, b * a); }
    RGBColor& operator*= (const float a);
    RGBColor operator/ (const float a) const { return RGBColor(r / a, g / a, b / a); }
    RGBColor& operator/= (const float a); 
    RGBColor operator* (const RGBColor& c) const { return RGBColor(r * c.r, g * c.g, b * c.b); }
    bool operator== (const RGBColor& c) const { return r == c.r && g == c.g && b == c.b; }

    RGBColor Pow(float p) const { return RGBColor(pow(r, p), pow(g, p), pow(b, p)); }
    float Average(void) const { return (0.333333333333 * (r + g + b)); }
};

// Inline member functions
inline RGBColor& RGBColor::operator+= (const RGBColor& c) {
    r += c.r; g += c.g; b += c.b;
    return *this;
}

inline RGBColor& RGBColor::operator*= (const float a) {
    r *= a; g *= a; b *= a;
    return *this;
}

inline RGBColor& RGBColor::operator/= (const float a) {	
    r /= a; g /= a; b /= a;
    return *this;
}

// Inline, non-member functions
inline RGBColor operator* (const float a, const RGBColor& c) {
    return RGBColor (a * c.r, a * c.g, a * c.b);	
}

#endif  // UTILITIES_RGB_COLOR_H_
