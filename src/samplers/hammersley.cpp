#include "samplers/hammersley.h"

#include <math.h>

#include "utilities/random.h"

Hammersley::Hammersley(const int numSamples): Sampler(numSamples) {
    GenerateSamples();
}

void Hammersley::GenerateSamples() {
    // Reset samples
    _samples.clear();
    _samples.reserve(numSamples() * numSets());

    double samplesInv = 1 / (double)numSamples();

    for (int p = 0; p < numSets(); p++) {
        for (int i = 0; i < numSamples(); i++) {
            Vector2D sp(i * samplesInv, Phi(i));
            _samples.push_back(sp);
        }
    }
}

double Hammersley::Phi(int j) {
    double x = 0.0;
    double f = 0.5;

    while (j) {
        x += f * (j & 1);
        j /= 2;
        f *= 0.5;
    }
    return x;
}
