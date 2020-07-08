#ifndef UTILITIES_CONSTANTS_H_
#define UTILITIES_CONSTANTS_H_

#include <stdlib.h>

#include "utilities/rgb_color.h"

const double kPi      = 3.1415926535897932384;
const double k2Pi     = 6.2831853071795864769;
const double kPiOver180   = 0.0174532925199432957;
const double kInvPi   = 0.3183098861837906715;
const double kInv2Pi  = 0.1591549430918953358;

const double kEpsilon   = 0.0001; 
const double kHugeValue = 1.0E10;

const RGBColor kBlack(0.0);
const RGBColor kWhite(1.0);
const RGBColor kRed(1.0, 0.0, 0.0);

const double kInvRandMax = 1.0 / (double)RAND_MAX;

#endif  // UTILITIES_CONSTANTS_H_
