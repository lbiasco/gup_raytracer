#include "utilities/rgb_color.h"

#include <math.h>

RGBColor::RGBColor(void) : r_(0.0), g_(0.0), b_(0.0) {}

RGBColor::RGBColor(float c) : r_(c), g_(c), b_(c) {}

RGBColor::RGBColor(float r, float g, float b)	: r_(r), g_(g), b_(b) {}

RGBColor::RGBColor(const RGBColor& c) : r_(c.r_), g_(c.g_), b_(c.b_) {}

RGBColor::~RGBColor(void) {}

RGBColor& RGBColor::operator= (const RGBColor& rhs) {
  if (this == &rhs)
    return *this;

  r_ = rhs.r_; g_ = rhs.g_; b_ = rhs.b_;
  return *this;
}

RGBColor RGBColor::Pow(float p) const {
  return (RGBColor(pow(r_, p), pow(g_, p), pow(b_, p)));
}
