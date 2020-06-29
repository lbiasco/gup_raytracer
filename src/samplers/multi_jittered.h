// This is the declaration of the class MultiJittered

#ifndef SAMPLERS_MULTI_JITTERED_H_
#define SAMPLERS_MULTI_JITTERED_H_

#include "samplers/sampler.h"

class MultiJittered : public Sampler {
	public:

		MultiJittered(const int num_samples);															
				
		virtual											
		~MultiJittered(void);		

        void    // generate sample patterns in a unit square
        GenerateSamples(void);
};

#endif  // SAMPLERS_MULTI_JITTERED_H_
