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


// -------------------------------------------------------------------- MapSamplesToUnitDisk

void
Sampler::MapSamplesToUnitDisk(void) {
    int size = samples_.size();
    float r, phi;   // polar coordinates
    Point2D sp;     // sample point on unit disk

    disk_samples_.reserve(size);

    for (int j = 0; j < size; j++) {
        // map sample point to [-1, 1]x[-1, 1]
        sp.x_ = 2.0 * samples_[j].x_ - 1.0;
        sp.y_ = 2.0 * samples_[j].y_ - 1.0;

        if (sp.x_ > -sp.y_) {           // sectors 1 and 2
            if (sp.x_ > sp.y_) {        // sector 1
                r = sp.x_;
                phi = sp.y_ / sp.x_;
            }
            else {                      // sector 2
                r = sp.y_;
                phi = 2 - sp.x_ / sp.y_;
            }
        }
        else {                          // sectors 3 and 4
            if (sp.x_ < sp.y_) {        // sector 3
                r = -sp.x_;
                phi = 4 + sp.y_ / sp.x_;
            }
            else {                      // sector 4
                r = -sp.y_;
                if (sp.y_ != 0.0)       // avoid division by zero at origin
                    phi = 6 - sp.x_ / sp.y_;
                else
                    phi = 0.0;
            }
        }

        phi *= kPi / 4.0;
        sp.x_ = r * cos(phi);
        sp.y_ = r * sin(phi);
        disk_samples_.push_back(sp); // NOTE: These points are still in [-1,1]x[-1,1]
    }
}


// -------------------------------------------------------------------- SampleUnitDisk

Point2D
Sampler::SampleUnitDisk(void) {
    if (count_ % num_samples_ == 0)
        jump_ = RandInt(num_sets_) * num_samples_;

    return disk_samples_[jump_ + shuffled_indices_[jump_ + count_++ % num_samples_]];
}


// -------------------------------------------------------------------- SampleUnitSquare

Point2D
Sampler::SampleUnitSquare(void) {
    if (count_ % num_samples_ == 0)
        jump_ = RandInt(num_sets_) * num_samples_;

    return samples_[jump_ + shuffled_indices_[jump_ + count_++ % num_samples_]];
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
