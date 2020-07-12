#ifndef SAMPLERS_MULTI_JITTERED_H_
#define SAMPLERS_MULTI_JITTERED_H_

#include "samplers/sampler.h"

// MultiJittered impementation of the Sampler object
class MultiJittered : public Sampler {
  public:
    // Constructors, destructors
    MultiJittered(const int num_samples);

    void GenerateSamples(void);
};

#endif  // SAMPLERS_MULTI_JITTERED_H_
