#ifndef SAMPLERS_SAMPLER_H_
#define SAMPLERS_SAMPLER_H_

#include <vector>

#include "utilities/point.h"

// Base class for Sampler Objects
class Sampler {
  public:
    // Constructors, destructors
    Sampler(const int num_samples);
    virtual ~Sampler(void);

    int GetNumSamples();
    void SetNumSamples(const int n);

    // generate sample patterns in a unit square
    virtual void GenerateSamples(void) = 0;

    void MapSamplesToHemisphere(const float e);
    void MapSamplesToUnitDisk(void);

    Point3D SampleHemisphere(void);
    Point2D SampleUnitDisk(void);
    Point2D SampleUnitSquare(void);

    void SetupShuffledIndices(void);

  protected:
    int num_samples_;               // the number of sample points in a pattern
    int num_sets_;                  // the number of sample sets (patterns) stored
    std::vector<Point2D> samples_;              // sample points on a unit square
    std::vector<Point2D> disk_samples_;         // sample points on a unit disk
    std::vector<Point3D> hemisphere_samples_;   // sample points on a hemisphere
    std::vector<int> shuffled_indices_;         // shuffled samples array indices
    unsigned long count_;           // the current number of sample points used
    int jump_;                      // random index jump
};

// Inline functions

inline int Sampler::GetNumSamples(void) {
  return num_samples_;
}

#endif  // SAMPLERS_SAMPLER_H_
