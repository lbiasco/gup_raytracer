#include <math.h>

#include "samplers/hammersley.h"
#include "utilities/random.h"

// -------------------------------------------------------------------- default constructor

Hammersley::Hammersley(const int num_samples): Sampler(num_samples) {
    GenerateSamples();
}


// -------------------------------------------------------------------- destructor

Hammersley::~Hammersley(void) {}


// -------------------------------------------------------------------- SetNumSamples

void
Hammersley::GenerateSamples() {
    double samples_inv = 1 / (double)num_samples_;

    for (int p = 0; p < num_sets_; p++)
        for (int i = 0; i < num_samples_; i++) {
            Point2D sp(i * samples_inv, Phi(i));
            samples_.push_back(sp);
        }
}


// -------------------------------------------------------------------- Phi

double
Hammersley::Phi(int j) {
    double x = 0.0;
    double f = 0.5;

    while (j) {
        x += f * (j & 1);
        j /= 2;
        f *= 0.5;
    }
    return (x);
}
