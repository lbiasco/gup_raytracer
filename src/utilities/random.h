#ifndef UTILITIES_RANDOM_H_
#define UTILITIES_RANDOM_H_

// Investigate replacing contents with <random>

#include <math.h>

#include "utilities/constants.h"

double          // Return a random double in [0, 1]
RandDouble();

int             // Return a random int in
RandInt(int range, int offset);

void            // Set random generation seed
SetRandSeet(int seed);

inline double
RandDouble() {
    return (double)rand() * kInvRandMax;
}

inline int
RandInt(int range=RAND_MAX, int offset=0) {
    /*
    int x;
    do {
        x = rand();
    } while (x >= (RAND_MAX - RAND_MAX % range));
    
    return x % range + offset;
     */
    return rand() % range + offset;
}

inline void
SetRandSeet(int seed) {
    srand(seed);
}

#endif  // UTILITIES_RANDOM_H_