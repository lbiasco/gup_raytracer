#include <numeric>
#include <vector>

#include "samplers/rooks.h"
#include "utilities/random.h"

// -------------------------------------------------------------------- default constructor

Rooks::Rooks(const int num_samples): Sampler(num_samples) {
    GenerateSamples();
}


// -------------------------------------------------------------------- destructor

Rooks::~Rooks(void) {}


// -------------------------------------------------------------------- SetNumSamples

void
Rooks::GenerateSamples() {
    double samples_inv = 1 / (double)num_samples_;
    std::vector<int> y_pos(num_samples_);

    for (int p = 0; p < num_sets_; p++) {
        // Fill a vector of potential y positions, from 0 to num_samples_
        std::iota(std::begin(y_pos), std::end(y_pos), 0);

        // Swap all the y positions to a random order
        for (int r = 0; r < num_samples_; r++)
            std::swap(y_pos[r], y_pos[RandInt(num_samples_)]);

        // Build samples using consecutive x and random-ordered y
        for (int r = 0; r < num_samples_; r++)
            samples_.push_back(Point2D((r + RandDouble()) * samples_inv, (y_pos[r] + RandDouble()) * samples_inv));
    }
}
