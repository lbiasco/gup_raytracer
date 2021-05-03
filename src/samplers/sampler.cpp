#include "samplers/sampler.h"

#include <algorithm>

#include "utilities/random.h"

Sampler::Sampler(const int numSamples) 
    : _numSamples(numSamples), _numSets(83), _count(0) {
  SetupShuffledIndices();
}

Sampler::~Sampler(void) {}

void Sampler::numSamples(int n) {
  _numSamples = n;
  SetupShuffledIndices();
  GenerateSamples();
}

void Sampler::MapSamplesToHemisphere(const float e) {
  int size = _samples.size();
  _hemisphereSamples.reserve(size);

  // x = r1, y = r2
  for (int j = 0; j < size; j++) {
    float cosPhi = cos(2.0 * kPi * _samples[j].x);
    float sinPhi = sin(2.0 * kPi * _samples[j].x);
    float cosTheta = pow((1.0 - _samples[j].y), 1.0 / (e + 1.0));
    float sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    
    float pu = sinTheta * cosPhi;
    float pv = sinTheta * sinPhi;
    float pw = cosTheta;

    _hemisphereSamples.push_back(Point3D(pu, pv, pw));
  }
}

void Sampler::MapSamplesToUnitDisk(void) {
  int size = _samples.size();
  float r, phi;   // polar coordinates
  Point2D sp;     // sample point on unit disk

  _diskSamples.reserve(size);
  for (int j = 0; j < size; j++) {
    // map sample point to [-1, 1]x[-1, 1]
    sp.x = 2.0 * _samples[j].x - 1.0;
    sp.y = 2.0 * _samples[j].y - 1.0;

    if (sp.x > -sp.y) {           // sectors 1 and 2
      if (sp.x > sp.y) {          // sector 1
        r = sp.x;
        phi = sp.y / sp.x;
      } else {                    // sector 2
        r = sp.y;
        phi = 2 - sp.x / sp.y;
      }
    } else {                      // sectors 3 and 4
      if (sp.x < sp.y) {          // sector 3
        r = -sp.x;
        phi = 4 + sp.y / sp.x;
      } else {                    // sector 4
        r = -sp.y;
        if (sp.y != 0.0)          // avoid division by zero at origin
          phi = 6 - sp.x / sp.y;
        else
          phi = 0.0;
      }
    }

    phi *= kPi / 4.0;
    sp.x = r * cos(phi);
    sp.y = r * sin(phi);
    _diskSamples.push_back(sp); // NOTE: These points are still in [-1,1]x[-1,1]
  }
}

Point3D Sampler::SampleHemisphere(void) {
  if (_count % _numSamples == 0)
    _jump = RandInt(_numSets) * _numSamples;

  return _hemisphereSamples[_jump + _shuffledIndices[_jump + _count++ % _numSamples]];
}

Point2D Sampler::SampleUnitDisk(void) {
  if (_count % _numSamples == 0)
    _jump = RandInt(_numSets) * _numSamples;

  return _diskSamples[_jump + _shuffledIndices[_jump + _count++ % _numSamples]];
}

Point2D Sampler::SampleUnitSquare(void) {
  if (_count % _numSamples == 0)
    _jump = RandInt(_numSets) * _numSamples;

  return _samples[_jump + _shuffledIndices[_jump + _count++ % _numSamples]];
}

void Sampler::SetupShuffledIndices(void) {
  _shuffledIndices.reserve(_numSamples * _numSets);
  std::vector<int> indices;

  for (int j = 0; j < _numSamples; j++)
    indices.push_back(j);

  for (int p = 0; p < _numSets; p++) {
    std::random_shuffle(indices.begin(), indices.end());

    for (int j = 0; j < _numSamples; j++)
      _shuffledIndices.push_back(indices[j]);
  }
}
