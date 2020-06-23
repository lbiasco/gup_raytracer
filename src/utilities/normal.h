
#ifndef UTILITIES_NORMAL_H_
#define UTILITIES_NORMAL_H_

// This file contains the declaration of the class Normal

#include "utilities/matrix.h"
#include "utilities/vector.h"
#include "utilities/point.h"

class Normal 
{	
	public:
	
		double	x_, y_, z_;
				
	public:
	
		Normal(void);										// default constructor
		Normal(double a);									// constructor
		Normal(double x, double y, double z);			// constructor
		Normal(const Normal& n); 							// copy constructor
		Normal(const Vector3D& v);							// constructs a normal from vector
		
		~Normal(void);										// destructor

		Normal& 											// assignment operator
		operator= (const Normal& rhs); 	
		
		Normal& 											// assignment of a vector to a normal
		operator= (const Vector3D& rhs);
		
		Normal& 											// assignment of a point to a normal
		operator= (const Point3D& rhs);
		
		Normal 												// unary minus
		operator- (void) const;	
		
		Normal 												// addition
		operator+ (const Normal& n) const;
		
		Normal& 											// compound addition
		operator+= (const Normal& n);
		
		double
		operator* (const Vector3D& v) const;				// dot product with a vector on the right
		
		Normal 												// multiplication by a double on the right
		operator* (const double a) const;
				
		void 												// convert normal to a unit normal
		Normalize(void); 									 		
};


// inlined member functions

// ----------------------------------------------------------------------- operator-
// unary minus

inline Normal 											
Normal::operator- (void) const {
	return (Normal(-x_, -y_, -z_));
}


// ----------------------------------------------------------------------- operator+
// addition of two normals

inline Normal 											
Normal::operator+ (const Normal& n) const {
	return (Normal(x_ + n.x_, y_ + n.y_, z_ + n.z_));
}


// ----------------------------------------------------------------------- addition
// compound addition of two normals

inline Normal& 
Normal::operator+= (const Normal& n) {
	x_ += n.x_; y_ += n.y_; z_ += n.z_;
    return (*this);
}


// ----------------------------------------------------------------------- operator*
// dot product of a normal on the left and a vector on the right

inline double
Normal::operator* (const Vector3D& v) const {
	return (x_ * v.x_ + y_ * v.y_ + z_ * v.z_);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a double on the right

inline Normal
Normal::operator* (const double a) const {
	return (Normal(x_ * a, y_ * a, z_ * a));
}


// inlined non-member functions

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

Normal
operator* (const double a, const Normal& n);

inline Normal
operator*(const double f, const Normal& n) {
	return (Normal(f * n.x_, f * n.y_, f * n.z_));
}


// ----------------------------------------------------------------------- operator+
// addition of a vector on the left to return a vector 

Vector3D
operator+ (const Vector3D& v, const Normal& n);

inline Vector3D
operator+ (const Vector3D& v, const Normal& n) {	
	return (Vector3D(v.x_ + n.x_, v.y_ + n.y_, v.z_ + n.z_));
}	


// ----------------------------------------------------------------------- operator-
// subtraction of a normal from a vector to return a vector

Vector3D
operator- (const Vector3D&, const Normal& n);

inline Vector3D
operator- (const Vector3D& v, const Normal& n) {
	return (Vector3D(v.x_ - n.x_, v.y_ - n.y_, v.z_ - n.z_));
}


// ----------------------------------------------------------------------- operator*
// dot product of a vector on the left and a normal on the right

double
operator* (const Vector3D& v, const Normal& n);

inline double
operator* (const Vector3D& v, const Normal& n) {
	return (v.x_ * n.x_ + v.y_ * n.y_ + v.z_ * n.z_);     
}


// non-inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a matrix on the left

Normal 											
operator* (const Matrix& mat, const Normal& n);

#endif  // UTILITIES_NORMAL_H_
