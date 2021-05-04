// This is the declaration of the class Regular

#ifndef SAMPLERS_REGULAR_H_
#define SAMPLERS_REGULAR_H_

#include "samplers/sampler.h"

// Regular impementation of the Sampler object
class Regular : public Sampler {
public:
    // Constructors, destructors
    Regular(const int numSamples);

    void GenerateSamples(void);
};

#endif  // SAMPLERS_REGULAR_H_
