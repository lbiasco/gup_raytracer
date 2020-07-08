#ifndef SAMPLERS_JITTERED_H_
#define SAMPLERS_JITTERED_H_

#include "samplers/sampler.h"

// Jittered impementation of the Sampler object
class Jittered : public Sampler {
  public:
    // Constructors, destructors
    Jittered(const int num_samples);
    ~Jittered(void) override;		

    void GenerateSamples(void);
};

#endif  // SAMPLERS_JITTERED_H_
