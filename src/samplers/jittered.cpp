#include <math.h>

#include "samplers/jittered.h"
#include "utilities/random.h"

// -------------------------------------------------------------------- default constructor

Jittered::Jittered(const int num_samples): Sampler(num_samples) {
    GenerateSamples();
}


// -------------------------------------------------------------------- destructor

Jittered::~Jittered(void) {}


// -------------------------------------------------------------------- SetNumSamples

void
Jittered::GenerateSamples() {
    int n = (int)sqrt(num_samples_);
    double n_inv = 1 / (double)n;

    for (int p = 0; p < num_sets_; p++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                Point2D sp((j + RandDouble()) * n_inv, (i + RandDouble()) * n_inv);
                samples_.push_back(sp);
            }
}
