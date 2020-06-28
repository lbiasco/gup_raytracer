// This is the declaration of the class Regular

#ifndef SAMPLERS_REGULAR_H_
#define SAMPLERS_REGULAR_H_

#include "samplers/sampler.h"

class Regular : public Sampler {
	public:

		Regular(const int num_samples);															
				
		virtual											
		~Regular(void);		

        void    // generate sample patterns in a unit square
        GenerateSamples(void);
};

#endif  // SAMPLERS_REGULAR_H_
