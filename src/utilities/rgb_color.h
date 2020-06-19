#ifndef UTILITIES_RGB_COLOR_H_
#define UTILITIES_RGB_COLOR_H_

// This file contains the declaration of the class RGBColor

//------------------------------------------------------------ class RGBColor

class RGBColor {
	
	public:
	
		float	r_, g_, b_;									
				
	public:
	
		RGBColor(void);										// default constructor
		RGBColor(float c);									// constructor
		RGBColor(float r, float g, float b);				// constructor
		RGBColor(const RGBColor& c); 						// copy constructor
		
		~RGBColor(void);									// destructor
		
		RGBColor& 											// assignment operator
		operator= (const RGBColor& rhs); 

		RGBColor 											// addition
		operator+ (const RGBColor& c) const;	

		RGBColor& 											// compound addition
		operator+= (const RGBColor& c);
		
		RGBColor 											// multiplication by a float on the right
		operator* (const float a) const;
		
		RGBColor& 											// compound multiplication by a float on the right
		operator*= (const float a);					
				
		RGBColor 											// division by a float
		operator/ (const float a) const;
		
		RGBColor& 											// compound division by a float
		operator/= (const float a); 
				
		RGBColor 											// component-wise multiplication
		operator* (const RGBColor& c) const;
		
		bool												// are two RGBColours the same?
		operator== (const RGBColor& c) const;				

		RGBColor											// raise components to a power
		Pow(float p) const;
		
		float												// the average of the components
		Average(void) const;
};


// inlined member functions

// ----------------------------------------------------------------------- operator+
// addition of two colors

inline RGBColor 
RGBColor::operator+ (const RGBColor& c) const {
	return (RGBColor(r_ + c.r_, g_ + c.g_, b_ + c.b_));
}


// ----------------------------------------------------------------------- operator+=
// compound addition of two colors

inline RGBColor& 
RGBColor::operator+= (const RGBColor& c) {
	r_ += c.r_; g_ += c.g_; b_ += c.b_;
    return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a float on the right

inline RGBColor 
RGBColor::operator* (const float a) const {
	return (RGBColor (r_ * a, g_ * a, b_ * a));	
}


// ----------------------------------------------------------------------- operator*=
// compound multiplication by a float on the right

inline RGBColor& 
RGBColor::operator*= (const float a) {
	r_ *= a; g_ *= a; b_ *= a;
	return (*this);
}


// ----------------------------------------------------------------------- operator/
// division by float

inline RGBColor 
RGBColor::operator/ (const float a) const {
	return (RGBColor (r_ / a, g_ / a, b_ / a));
}


// ----------------------------------------------------------------------- operator/=
// compound division by float

inline RGBColor& 
RGBColor::operator/= (const float a) {	
	r_ /= a; g_ /= a; b_ /= a;
	return (*this);
}


// ----------------------------------------------------------------------- operator*
// component-wise multiplication of two colors

inline RGBColor 
RGBColor::operator* (const RGBColor& c) const {
	return (RGBColor (r_ * c.r_, g_ * c.g_, b_ * c.b_));
} 


// ----------------------------------------------------------------------- operator==
// are two RGBColors the same?

inline bool
RGBColor::operator== (const RGBColor& c) const {
	return (r_ == c.r_ && g_ == c.g_ && b_ == c.b_);
}


// ----------------------------------------------------------------------- Average
// the average of the three components

inline float											
RGBColor::Average(void) const {
	return (0.333333333333 * (r_ + g_ + b_));
}


// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a float on the left

RGBColor 
operator* (const float a, const RGBColor& c);

inline RGBColor 
operator* (const float a, const RGBColor& c) {
	return (RGBColor (a * c.r_, a * c.g_, a * c.b_));	
}


#endif  // UTILITIES_RGB_COLOR_H_
