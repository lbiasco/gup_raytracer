#include "samplers/random.h"

#include <math.h>

#include "utilities/random.h"

Random::Random(const int numSamples) : Sampler(numSamples) {
  GenerateSamples();
}

void Random::GenerateSamples() {
  int n = (int)sqrt(numSamples());
  double nInv = 1 / (double)n;

  for (int p = 0; p < numSets(); p++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        Point2D sp(RandDouble(), RandDouble());
        _samples.push_back(sp);
      }
}
