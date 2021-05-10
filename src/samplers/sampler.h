#ifndef SAMPLERS_SAMPLER_H_
#define SAMPLERS_SAMPLER_H_

#include <vector>

#include "utilities/vector.h"

// Base class for Sampler Objects
class Sampler {
public:
    // Constructors, destructors
    Sampler(const int numSamples);
    virtual ~Sampler();

    void numSamples(int n);
    int numSamples() const { return _numSamples; }

    int numSets() const { return _numSets; }

    // generate sample patterns in a unit square
    virtual void GenerateSamples() = 0;

    void MapSamplesToHemisphere(const float e);
    void MapSamplesToUnitDisk();

    Vector3D SampleHemisphere();
    Vector2D SampleUnitDisk();
    Vector2D SampleUnitSquare();

    void SetupShuffledIndices();

protected:
    std::vector<Vector2D> _samples;  // sample points on a unit square

private:
    int _numSamples;               // the number of sample points in a pattern
    int _numSets;                  // the number of sample sets (patterns) stored
    std::vector<Vector2D> _diskSamples;         // sample points on a unit disk
    std::vector<Vector3D> _hemisphereSamples;   // sample points on a hemisphere
    std::vector<int> _shuffledIndices;         // shuffled samples array indices
    unsigned long _count;           // the current number of sample points used
    int _jump;                      // random index jump
};

#endif  // SAMPLERS_SAMPLER_H_
