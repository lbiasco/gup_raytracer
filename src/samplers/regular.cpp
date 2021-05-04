#include "samplers/regular.h"

#include <math.h>

#include "utilities/random.h"

Regular::Regular(const int numSamples): Sampler(numSamples) {
    GenerateSamples();
}

void Regular::GenerateSamples() {
    int n = (int)sqrt(numSamples());
    double nInv = 1 / (double)n;

    for (int p = 0; p < numSets(); p++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Point2D sp((j + 0.5) * nInv, (i + 0.5) * nInv);
                _samples.push_back(sp);
            }
        }
    }
}
