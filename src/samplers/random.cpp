#include <math.h>

#include "samplers/random.h"
#include "utilities/random.h"

// -------------------------------------------------------------------- default constructor

Random::Random(const int num_samples): Sampler(num_samples) {
    GenerateSamples();
}


// -------------------------------------------------------------------- destructor

Random::~Random(void) {}


// -------------------------------------------------------------------- SetNumSamples

void
Random::GenerateSamples() {
    int n = (int)sqrt(num_samples_);
    double nInv = 1 / (double)n;

    for (int p = 0; p < num_sets_; p++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                Point2D sp(RandDouble(), RandDouble());
                samples_.push_back(sp);
            }
}
