#include "samplers/regular.h"

#include <math.h>

#include "utilities/random.h"

Regular::Regular(const int num_samples): Sampler(num_samples) {
    GenerateSamples();
}

void Regular::GenerateSamples() {
  int n = (int)sqrt(num_samples());
  double nInv = 1 / (double)n;

  for (int p = 0; p < num_sets(); p++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        Point2D sp((j + 0.5) * nInv, (i + 0.5) * nInv);
        samples_.push_back(sp);
      }
}
