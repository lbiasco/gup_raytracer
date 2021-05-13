#include "samplers/rooks.h"

#include <numeric>
#include <vector>

#include "utilities/random.h"

Rooks::Rooks(const int numSamples) : Sampler(numSamples) {
    GenerateSamples();
}

void Rooks::GenerateSamples() {
    // Reset samples
    _samples.clear();
    _samples.reserve(numSamples() * numSets());

    double samplesInv = 1 / (double)numSamples();

    for (int p = 0; p < numSets(); p++) {
        std::vector<Vector2D> sampleSet;
        sampleSet.reserve(numSamples());

        // Initialize set with jittered samples along diagonal
        for (int i = 0; i < numSamples(); i++) {
            Vector2D sample((i + RandDouble()) * samplesInv, (i + RandDouble()) * samplesInv);
            sampleSet.push_back(sample);
        }

        // TODO? Rather than shuffling in-place Vector2Ds, it would be more 
        // efficient to generate pre-shuffled lists of x and y values to pair up
        
        // Shuffle X coordinates
        for (int i = 0; i < numSamples(); i++) {
            int target = RandInt(numSamples());
            float temp = sampleSet[i].x;
            sampleSet[i].x = sampleSet[target].x;
            sampleSet[target].x = temp;
        }

        // Shuffle Y coordinates
        for (int i = 0; i < numSamples(); i++) {
            int target = RandInt(numSamples());
            float temp = sampleSet[i].y;
            sampleSet[i].y = sampleSet[target].y;
            sampleSet[target].y = temp;
        }

        // Add sample set to data member
        _samples.insert(_samples.end(), sampleSet.begin(), sampleSet.end());
    }
}
