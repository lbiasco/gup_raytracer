// This is the declaration of the class Random

#ifndef SAMPLERS_RANDOM_H_
#define SAMPLERS_RANDOM_H_

#include "samplers/sampler.h"

class Random : public Sampler {
	public:

		Random(const int num_samples);															
				
		virtual											
		~Random(void);		

        void    // generate sample patterns in a unit square
        GenerateSamples(void);
};

#endif  // SAMPLERS_RANDOM_H_
