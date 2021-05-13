#ifndef SAMPLERS_JITTERED_H_
#define SAMPLERS_JITTERED_H_

#include "samplers/sampler.h"

// Jittered impementation of the Sampler object
class Jittered : public Sampler {
    public:
        // Constructors, destructors
        Jittered(const int numSamples);

        void GenerateSamples();
};

#endif  // SAMPLERS_JITTERED_H_
