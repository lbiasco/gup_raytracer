#include "samplers/multi_jittered.h"

#include <math.h>
#include <numeric>
#include <vector>

#include "utilities/random.h"

MultiJittered::MultiJittered(const int num_samples) : Sampler(num_samples) {
  GenerateSamples();
}

MultiJittered::~MultiJittered(void) {}

void MultiJittered::GenerateSamples() {
  int n = (int)sqrt(num_samples_);
  double n_inv = 1 / (double)n;
  std::vector<Point2D> inner_pos(num_samples_);

  for (int p = 0; p < num_sets_; p++) {
    // Generate a list of point offsets for each inner grid
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        inner_pos.push_back(Point2D(j * n_inv * n_inv, i * n_inv * n_inv));

    // Swap all the point offsets to a random order
    for (int r = 0; r < num_samples_; r++)
      std::swap(inner_pos[r], inner_pos[RandInt(num_samples_)]);

    // Iterate through all inner grids, adding jitter and offset to fit in overall grid
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        Point2D pp;
        pp.x_ = j * n_inv + inner_pos[i+j].x_;
        pp.y_ = i * n_inv + inner_pos[i+j].y_;
        samples_.push_back(pp);
      }
    }
  }
}
