// This is the declaration of the class Jittered

#ifndef SAMPLERS_JITTERED_H_
#define SAMPLERS_JITTERED_H_

#include "samplers/sampler.h"

class Jittered : public Sampler {
	public:

		Jittered(const int num_samples);															
				
		virtual											
		~Jittered(void);		

        void    // generate sample patterns in a unit square
        GenerateSamples(void);
};

#endif  // SAMPLERS_JITTERED_H_
