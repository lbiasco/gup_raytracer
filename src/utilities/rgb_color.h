#ifndef UTILITIES_RGB_COLOR_H_
#define UTILITIES_RGB_COLOR_H_

class RGBColor {
  public:
    RGBColor(void);
    RGBColor(float c);
    RGBColor(float r, float g, float b);
    RGBColor(const RGBColor& c);
    ~RGBColor(void);

    RGBColor&  operator= (const RGBColor& rhs); 
    RGBColor operator+ (const RGBColor& c) const;
    RGBColor& operator+= (const RGBColor& c);
    RGBColor operator* (const float a) const;
    RGBColor& operator*= (const float a);
    RGBColor operator/ (const float a) const;
    RGBColor& operator/= (const float a); 
    RGBColor operator* (const RGBColor& c) const;
    bool operator== (const RGBColor& c) const;

    RGBColor Pow(float p) const;
    float Average(void) const;

    float	r_, g_, b_;
};

// Inline member functions
inline RGBColor RGBColor::operator+ (const RGBColor& c) const {
  return RGBColor(r_ + c.r_, g_ + c.g_, b_ + c.b_);
}

inline RGBColor& RGBColor::operator+= (const RGBColor& c) {
  r_ += c.r_; g_ += c.g_; b_ += c.b_;
  return *this;
}

inline RGBColor RGBColor::operator* (const float a) const {
  return RGBColor (r_ * a, g_ * a, b_ * a);	
}

inline RGBColor& RGBColor::operator*= (const float a) {
  r_ *= a; g_ *= a; b_ *= a;
  return *this;
}

inline RGBColor RGBColor::operator/ (const float a) const {
  return RGBColor (r_ / a, g_ / a, b_ / a);
}

inline RGBColor& RGBColor::operator/= (const float a) {	
  r_ /= a; g_ /= a; b_ /= a;
  return *this;
}

inline RGBColor RGBColor::operator* (const RGBColor& c) const {
  return RGBColor (r_ * c.r_, g_ * c.g_, b_ * c.b_);
} 

inline bool RGBColor::operator== (const RGBColor& c) const {
  return r_ == c.r_ && g_ == c.g_ && b_ == c.b_;
}

inline float RGBColor::Average(void) const {
  return (0.333333333333 * (r_ + g_ + b_));
}


// Inline, non-member functions

RGBColor operator* (const float a, const RGBColor& c);
inline RGBColor operator* (const float a, const RGBColor& c) {
  return RGBColor (a * c.r_, a * c.g_, a * c.b_);	
}

#endif  // UTILITIES_RGB_COLOR_H_
