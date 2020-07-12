#include "samplers/hammersley.h"

#include <math.h>

#include "utilities/random.h"

Hammersley::Hammersley(const int num_samples): Sampler(num_samples) {
  GenerateSamples();
}

void Hammersley::GenerateSamples() {
  double samples_inv = 1 / (double)num_samples();

  for (int p = 0; p < num_sets(); p++)
    for (int i = 0; i < num_samples(); i++) {
      Point2D sp(i * samples_inv, Phi(i));
      samples_.push_back(sp);
    }
}

double Hammersley::Phi(int j) {
  double x = 0.0;
  double f = 0.5;

  while (j) {
    x += f * (j & 1);
    j /= 2;
    f *= 0.5;
  }
  return x;
}
