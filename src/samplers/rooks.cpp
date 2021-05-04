#include "samplers/rooks.h"

#include <numeric>
#include <vector>

#include "utilities/random.h"

Rooks::Rooks(const int numSamples) : Sampler(numSamples) {
    GenerateSamples();
}

void Rooks::GenerateSamples() {
    double samplesInv = 1 / (double)numSamples();
    std::vector<int> yPos(numSamples());

    for (int p = 0; p < numSets(); p++) {
        // Fill a vector of potential y positions, from 0 to numSamples
        std::iota(std::begin(yPos), std::end(yPos), 0);

        // Swap all the y positions to a random order
        for (int r = 0; r < numSamples(); r++)
            std::swap(yPos[r], yPos[RandInt(numSamples())]);

        // Build samples using consecutive x and random-ordered y
        for (int r = 0; r < numSamples(); r++)
            _samples.push_back(Point2D((r + RandDouble()) * samplesInv, (yPos[r] + RandDouble()) * samplesInv));
    }
}
