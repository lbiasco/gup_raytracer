// This is the declaration of the class Rooks

#ifndef SAMPLERS_ROOKS_H_
#define SAMPLERS_ROOKS_H_

#include "samplers/sampler.h"

class Rooks : public Sampler {
	public:

		Rooks(const int num_samples);															
				
		virtual											
		~Rooks(void);		

        void    // generate sample patterns in a unit square
        GenerateSamples(void);
};

#endif  // SAMPLERS_ROOKS_H_
