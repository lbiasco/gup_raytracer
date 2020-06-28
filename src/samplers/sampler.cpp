#include "samplers/sampler.h"
#include "utilities/random.h"

// -------------------------------------------------------------------- default constructor

Sampler::Sampler(const int num_samples)
	: num_samples_(num_samples), num_sets_(83), count_(0) {}


// -------------------------------------------------------------------- destructor

Sampler::~Sampler(void) {}


// -------------------------------------------------------------------- SetNumSamples

void
Sampler::SetNumSamples(const int n) {
    num_samples_ = n;
    GenerateSamples();
}


// -------------------------------------------------------------------- SampleUnitSquare

Point2D
Sampler::SampleUnitSquare(void) {
    if (count_ % num_samples_ == 0)
        jump_ = RandInt(num_sets_) * num_samples_;

    return samples_[jump_ + count_++ % num_samples_];
}

