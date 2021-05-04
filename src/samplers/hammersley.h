#ifndef SAMPLERS_HAMMERSLEY_H_
#define SAMPLERS_HAMMERSLEY_H_

#include "samplers/sampler.h"

// Hammersley impementation of the Sampler object
class Hammersley : public Sampler {
public:
    // Constructors, destructors
    Hammersley(const int numSamples);

    void GenerateSamples();

private:
    // radical inverse function for base 2
    double Phi(int j);
};

#endif  // SAMPLERS_HAMMERSLEY_H_
