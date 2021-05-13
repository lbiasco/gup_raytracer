#include "samplers/jittered.h"

#include <math.h>

#include "utilities/random.h"

Jittered::Jittered(const int numSamples): Sampler(numSamples) {
    GenerateSamples();
}

void Jittered::GenerateSamples() {
    // Reset samples
    _samples.clear();
    _samples.reserve(numSamples() * numSets());

    int n = (int)sqrt(numSamples());
    double n_inv = 1 / (double)n;

    for (int p = 0; p < numSets(); p++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Vector2D sp((j + RandDouble()) * n_inv, (i + RandDouble()) * n_inv);
                _samples.push_back(sp);
            }
        }
    }
}
