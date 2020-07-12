#include "samplers/sampler.h"

#include <algorithm>

#include "utilities/random.h"

Sampler::Sampler(const int num_samples) 
    : num_samples_(num_samples), num_sets_(83), count_(0) {
  SetupShuffledIndices();
}

Sampler::~Sampler(void) {}

void Sampler::num_samples(int n) {
  num_samples_ = n;
  SetupShuffledIndices();
  GenerateSamples();
}

void Sampler::MapSamplesToHemisphere(const float e) {
  int size = samples_.size();
  hemisphere_samples_.reserve(size);

  // x = r1, y = r2
  for (int j = 0; j < size; j++) {
    float cos_phi = cos(2.0 * kPi * samples_[j].x);
    float sin_phi = sin(2.0 * kPi * samples_[j].x);
    float cos_theta = pow((1.0 - samples_[j].y), 1.0 / (e + 1.0));
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    
    float pu = sin_theta * cos_phi;
    float pv = sin_theta * sin_phi;
    float pw = cos_theta;

    hemisphere_samples_.push_back(Point3D(pu, pv, pw));
  }
}

void Sampler::MapSamplesToUnitDisk(void) {
  int size = samples_.size();
  float r, phi;   // polar coordinates
  Point2D sp;     // sample point on unit disk

  disk_samples_.reserve(size);
  for (int j = 0; j < size; j++) {
    // map sample point to [-1, 1]x[-1, 1]
    sp.x = 2.0 * samples_[j].x - 1.0;
    sp.y = 2.0 * samples_[j].y - 1.0;

    if (sp.x > -sp.y) {           // sectors 1 and 2
      if (sp.x > sp.y) {          // sector 1
        r = sp.x;
        phi = sp.y / sp.x;
      } else {                    // sector 2
        r = sp.y;
        phi = 2 - sp.x / sp.y;
      }
    } else {                      // sectors 3 and 4
      if (sp.x < sp.y) {          // sector 3
        r = -sp.x;
        phi = 4 + sp.y / sp.x;
      } else {                    // sector 4
        r = -sp.y;
        if (sp.y != 0.0)          // avoid division by zero at origin
          phi = 6 - sp.x / sp.y;
        else
          phi = 0.0;
      }
    }

    phi *= kPi / 4.0;
    sp.x = r * cos(phi);
    sp.y = r * sin(phi);
    disk_samples_.push_back(sp); // NOTE: These points are still in [-1,1]x[-1,1]
  }
}

Point3D Sampler::SampleHemisphere(void) {
  if (count_ % num_samples_ == 0)
    jump_ = RandInt(num_sets_) * num_samples_;

  return hemisphere_samples_[jump_ + shuffled_indices_[jump_ + count_++ % num_samples_]];
}

Point2D Sampler::SampleUnitDisk(void) {
  if (count_ % num_samples_ == 0)
    jump_ = RandInt(num_sets_) * num_samples_;

  return disk_samples_[jump_ + shuffled_indices_[jump_ + count_++ % num_samples_]];
}

Point2D Sampler::SampleUnitSquare(void) {
  if (count_ % num_samples_ == 0)
    jump_ = RandInt(num_sets_) * num_samples_;

  return samples_[jump_ + shuffled_indices_[jump_ + count_++ % num_samples_]];
}

void Sampler::SetupShuffledIndices(void) {
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
