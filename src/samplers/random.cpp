#include "samplers/random.h"

#include <math.h>

#include "utilities/random.h"

Random::Random(const int num_samples) : Sampler(num_samples) {
  GenerateSamples();
}

Random::~Random(void) {}

void Random::GenerateSamples() {
  int n = (int)sqrt(num_samples_);
  double nInv = 1 / (double)n;

  for (int p = 0; p < num_sets_; p++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        Point2D sp(RandDouble(), RandDouble());
        samples_.push_back(sp);
      }
}
