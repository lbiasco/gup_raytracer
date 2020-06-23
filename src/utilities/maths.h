#ifndef UTILITIES_MATHS_H_
#define UTILITIES_MATHS_H_

#include <math.h>

#include "utilities/constants.h"

inline double
Max(double x0, double x1);

inline double
RandDouble();

inline double
Max(double x0, double x1) {
	return ((x0 > x1) ? x0 : x1);
}

inline double
RandDouble() {
    return (double)rand() * kInvRandMax;
}

#endif  // UTILITIES_MATHS_H_
