#include "samplers/multi_jittered.h"

#include <math.h>
#include <numeric>
#include <vector>

#include "utilities/random.h"

MultiJittered::MultiJittered(const int numSamples) : Sampler(numSamples) {
  GenerateSamples();
}

void MultiJittered::GenerateSamples() {
  int n = (int)sqrt(numSamples());
  double n_inv = 1 / (double)n;
  std::vector<Point2D> innerPos(numSamples());

  for (int p = 0; p < numSets(); p++) {
    // Generate a list of point offsets for each inner grid
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        innerPos.push_back(Point2D(j * n_inv * n_inv, i * n_inv * n_inv));

    // Swap all the point offsets to a random order
    for (int r = 0; r < numSamples(); r++)
      std::swap(innerPos[r], innerPos[RandInt(numSamples())]);

    // Iterate through all inner grids, adding jitter and offset to fit in overall grid
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        Point2D pp;
        pp.x = j * n_inv + innerPos[i+j].x;
        pp.y = i * n_inv + innerPos[i+j].y;
        _samples.push_back(pp);
      }
    }
  }
}
