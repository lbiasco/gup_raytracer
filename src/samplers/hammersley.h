// This is the declaration of the class Hammersley

#ifndef SAMPLERS_HAMMERSLEY_H_
#define SAMPLERS_HAMMERSLEY_H_

#include "samplers/sampler.h"

class Hammersley : public Sampler {
	public:

		Hammersley(const int num_samples);															
				
		virtual											
		~Hammersley(void);		

        void    // generate sample patterns in a unit square
        GenerateSamples(void);

        double  // radical inverse function for base 2
        Phi(int j);
};

#endif  // SAMPLERS_HAMMERSLEY_H_
