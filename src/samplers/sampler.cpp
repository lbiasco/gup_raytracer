#include <algorithm>

#include "samplers/sampler.h"
#include "utilities/random.h"

// -------------------------------------------------------------------- default constructor

Sampler::Sampler(const int num_samples)
	: num_samples_(num_samples), num_sets_(83), count_(0) {
    SetupShuffledIndices();
}


// -------------------------------------------------------------------- destructor

Sampler::~Sampler(void) {}


// -------------------------------------------------------------------- SetNumSamples

void
Sampler::SetNumSamples(const int n) {
    num_samples_ = n;
    SetupShuffledIndices();
    GenerateSamples();
}


// -------------------------------------------------------------------- SetupShuffledIndices

void
Sampler::SetupShuffledIndices(void) {
    shuffled_indices_.reserve(num_samples_ * num_sets_);
    std::vector<int> indices;

    for (int j = 0; j < num_samples_; j++)
        indices.push_back(j);

    for (int p = 0; p < num_sets_; p++) {
        std::random_shuffle(indices.begin(), indices.end());

        for (int j = 0; j < num_samples_; j++)
            shuffled_indices_.push_back(indices[j]);
    }
}


// -------------------------------------------------------------------- SampleUnitSquare

Point2D
Sampler::SampleUnitSquare(void) {
    if (count_ % num_samples_ == 0)
        jump_ = RandInt(num_sets_) * num_samples_;

    return samples_[jump_ + shuffled_indices_[jump_ + count_++ % num_samples_]];
}

