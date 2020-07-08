#ifndef UTILITIES_RANDOM_H_
#define UTILITIES_RANDOM_H_

// Investigate replacing contents with <random>

#include <math.h>

#include "utilities/constants.h"

// Return a random double in [0, 1]
inline double RandDouble(void) {
  return (double)rand() * kInvRandMax;
}

// Return a random int in
inline int RandInt(int range=RAND_MAX, int offset=0) {
  int x;
  do {
      x = rand();
  } while (x >= (RAND_MAX - RAND_MAX % range));
  return x % range + offset;
}

// Set random generation seed
inline void SetRandSeet(int seed) {
    srand(seed);
}

#endif  // UTILITIES_RANDOM_H_