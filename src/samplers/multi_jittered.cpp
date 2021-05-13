#include "samplers/multi_jittered.h"

#include <math.h>
#include <algorithm>
#include <numeric>
#include <vector>

#include "utilities/random.h"

MultiJittered::MultiJittered(const int numSamples) : Sampler(numSamples) {
    GenerateSamples();
}

void MultiJittered::GenerateSamples() {
    // Reset samples
    _samples.clear();
    _samples.reserve(numSamples() * numSets());

    // Not sure if this is still considered multi-jittered, but instead of
    // laying out all sample points and then randomly shuffling them, I'm 
    // going to just create a list of lists that describes what open positions 
    // are left in a given super-grid row/column. Who knows which is "better", 
    // I'm not doing any analysis.
    int n = (int)sqrt(numSamples());
    int nSq = n * n;
    double nSqInv = 1 / (double)nSq;

    for (int p = 0; p < numSets(); p++) {
        std::vector<Vector2D> sampleSet;
        sampleSet.reserve(numSamples());

        // Generate list of vectors for each possible position in a super-grid 
        // row/column and randomly shuffle order
        std::vector<int> rows[n];
        std::vector<int> columns[n];
        for (int i = 0; i < n; i++) {
            std::vector<int> row(n);
            std::vector<int> column(n);
            // Initialize positions
            std::iota(row.begin(), row.end(), i * n);
            std::iota(column.begin(), column.end(), i * n);
            // Randomly shuffle positions
            std::random_shuffle(row.begin(), row.end());
            std::random_shuffle(column.begin(), column.end());
            // Assign to lists
            rows[i] = row;
            columns[i] = column;
        }

        // Loop through every super-grid cell, pulling from lists of random positions 
        // and shrinking down to a 1x1 square
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Also add random jitter to sub-grid cell
                float x = (rows[i].back() + RandDouble()) * nSqInv;
                rows[i].pop_back();

                float y = (columns[j].back() + RandDouble()) * nSqInv;
                columns[j].pop_back();

                sampleSet.push_back(Vector2D(x, y));
            }
        }

        // If the expected number of samples isn't a perfect square, add 
        // random samples to the set to reach it
        for (int i = 0; i < numSamples() - nSq; i++) {
            sampleSet.push_back(Vector2D(RandDouble(), RandDouble()));
        }

        // Add sample set to data member
        _samples.insert(_samples.end(), sampleSet.begin(), sampleSet.end());
    }
}
