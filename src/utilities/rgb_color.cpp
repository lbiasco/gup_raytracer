#include "utilities/rgb_color.h"

// Implementations of struct RBGColor

RGBColor& RGBColor::operator= (const RGBColor& rhs) {
    if (this == &rhs)
        return *this;

    r = rhs.r; g = rhs.g; b = rhs.b;
    return *this;
}
