#ifndef SAMPLERS_ROOKS_H_
#define SAMPLERS_ROOKS_H_

#include "samplers/sampler.h"

// Rooks impementation of the Sampler object
class Rooks : public Sampler {
public:
    // Constructors, destructors
    Rooks(const int numSamples);

    void GenerateSamples(void);
};

#endif  // SAMPLERS_ROOKS_H_
