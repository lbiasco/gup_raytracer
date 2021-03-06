#include "samplers/random.h"

#include <math.h>

#include "utilities/random.h"

Random::Random(const int numSamples) : Sampler(numSamples) {
    GenerateSamples();
}

void Random::GenerateSamples() {
    // Reset samples
    _samples.clear();
    _samples.reserve(numSamples() * numSets());

    int n = (int)sqrt(numSamples());
    double nInv = 1 / (double)n;

    for (int p = 0; p < numSets(); p++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Vector2D sp(RandDouble(), RandDouble());
                _samples.push_back(sp);
            }
        }
    }
}
