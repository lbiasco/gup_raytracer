
#ifndef SAMPLERS_RANDOM_H_
#define SAMPLERS_RANDOM_H_

#include "samplers/sampler.h"

// Random impementation of the Sampler object
class Random : public Sampler {
  public:
    // Constructors, destructors
    Random(const int num_samples);

    void GenerateSamples(void);
};

#endif  // SAMPLERS_RANDOM_H_
