// This is the declaration of the base class Sampler

#ifndef SAMPLERS_SAMPLER_H_
#define SAMPLERS_SAMPLER_H_

#include <vector>

#include "utilities/point.h"

class Sampler {
	public:
	
		Sampler(const int num_samples);															
				
		virtual											
		~Sampler(void);		

        int             // get the number of samples
        GetNumSamples();

        void            // get the number of samples
        SetNumSamples(const int n);

        virtual void    // generate sample patterns in a unit square
        GenerateSamples(void) = 0;

        void            // map square sample patterns to hemisphere
        MapSamplesToHemisphere(const float e);

        void            // map square sample patterns to unit disk
        MapSamplesToUnitDisk(void);

        Point3D         // get next sample on hemisphere
        SampleHemisphere(void);

        Point2D         // get next sample on unit disk
        SampleUnitDisk(void);

        Point2D         // get next sample on unit square
        SampleUnitSquare(void);

        void            // set up the randomly shuffled indices
        SetupShuffledIndices(void);

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


// ------------------------------------------------------------------------------ GetNumSamples

inline int											
Sampler::GetNumSamples(void) {
	return num_samples_;
}

#endif  // SAMPLERS_SAMPLER_H_
