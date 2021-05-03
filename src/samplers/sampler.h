#ifndef SAMPLERS_SAMPLER_H_
#define SAMPLERS_SAMPLER_H_

#include <vector>

#include "utilities/point.h"

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

    Point3D SampleHemisphere();
    Point2D SampleUnitDisk();
    Point2D SampleUnitSquare();

    void SetupShuffledIndices();

  protected:
    std::vector<Point2D> _samples;  // sample points on a unit square

  private:
    int _numSamples;               // the number of sample points in a pattern
    int _numSets;                  // the number of sample sets (patterns) stored
    std::vector<Point2D> _diskSamples;         // sample points on a unit disk
    std::vector<Point3D> _hemisphereSamples;   // sample points on a hemisphere
    std::vector<int> _shuffledIndices;         // shuffled samples array indices
    unsigned long _count;           // the current number of sample points used
    int _jump;                      // random index jump
};

#endif  // SAMPLERS_SAMPLER_H_
