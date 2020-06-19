#ifndef UTILITIES_VECTOR_3D_H_
#define UTILITIES_VECTOR_3D_H_

// This file contains the declaration of the class Vector3D

#include "utilities/matrix.h"

class Normal;
class Point3D;

//----------------------------------------- class Vector3D

class Vector3D {
	public:
	
		double	x_, y_, z_;

	public:
	
		Vector3D(void);											// default constructor
		Vector3D(double a);										// constructor
		Vector3D(double x, double y, double z);				// constructor
		Vector3D(const Vector3D& v);							// copy constructor
		Vector3D(const Normal& n);								// constructs a vector from a Normal
		Vector3D(const Point3D& p);								// constructs a vector from a point

		~Vector3D (void);										// destructor

		Vector3D& 												// assignment operator
		operator= (const Vector3D& rhs);
		
		Vector3D& 												// assign a Normal to a vector
		operator= (const Normal& rhs); 
		
		Vector3D& 												// assign a Point3D to a vector
		operator= (const Point3D& rhs); 
		
		Vector3D												// unary minus
		operator- (void) const;									
				
		double													// length
		Length(void);
		
		double													// square of the length
		LengthSquared(void);
		
		Vector3D												// multiplication by a double on the right
		operator* (const double a) const;
				
		Vector3D												// division by a double
		operator/ (const double a) const;
		
		Vector3D												// addition
		operator+ (const Vector3D& v) const;
		
		Vector3D& 												// compound addition
		operator+= (const Vector3D& v);					
		
		Vector3D												// subtraction
		operator- (const Vector3D& v) const;					
		
		double 													// dot product							
		operator* (const Vector3D& b) const;
		
		Vector3D 												// cross product				
		operator^ (const Vector3D& v) const;
		
		void 													// convert vector to a unit vector
		Normalize(void); 
		
		Vector3D& 												// return a unit vector, and normalize the vector												
		Hat(void);
};


// inlined member functions

// ------------------------------------------------------------------------ unary minus
// this does not change the current vector
// this allows ShadeRec objects to be declared as constant arguments in many shading
// functions that reverse the direction of a ray that's stored in the ShadeRec object

inline Vector3D 
Vector3D::operator- (void) const {
	return (Vector3D(-x_, -y_, -z_));    
}


// ---------------------------------------------------------------------  LengthSquared
// the square of the length

inline double													
Vector3D::LengthSquared(void) {	
	return (x_ * x_ + y_ * y_ + z_ * z_);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a double on the right

inline Vector3D
Vector3D::operator* (const double a) const {	
	return (Vector3D(x_ * a, y_ * a, z_ * a));	
}

// ----------------------------------------------------------------------- operator/
// division by a double

inline Vector3D
Vector3D::operator/ (const double a) const {	
	return (Vector3D(x_ / a, y_ / a, z_ / a));	
}


// ----------------------------------------------------------------------- operator+
// addition

inline Vector3D
Vector3D::operator+ (const Vector3D& v) const {
	return (Vector3D(x_ + v.x_, y_ + v.y_, z_ + v.z_));
}


// ----------------------------------------------------------------------- operator-
// subtraction

inline Vector3D
Vector3D::operator- (const Vector3D& v) const {
	return (Vector3D(x_ - v.x_, y_ - v.y_, z_ - v.z_));
}


// ----------------------------------------------------------------------- operator*
// dot product

inline double 
Vector3D::operator* (const Vector3D& v) const {
	return (x_ * v.x_ + y_ * v.y_ + z_ * v.z_);
} 


// ----------------------------------------------------------------------- operator^
// cross product

inline Vector3D 									
Vector3D::operator^ (const Vector3D& v) const {
	return (Vector3D(y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_));
}


// ---------------------------------------------------------------------  operator+=
// compound addition

inline Vector3D& 
Vector3D::operator+= (const Vector3D& v) {
	x_ += v.x_; y_ += v.y_; z_ += v.z_;
	return (*this);
}


// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

Vector3D 
operator* (const double a, const Vector3D& v);

inline Vector3D 
operator* (const double a, const Vector3D& v) {
	return (Vector3D(a * v.x_, a * v.y_, a * v.z_));	
}


// non-inlined non-member function

// ----------------------------------------------------------------------- operator* 
// multiplication by a matrix on the left

Vector3D 
operator* (const Matrix& mat, const Vector3D& v);


#endif  // UTILITIES_VECTOR_3D_H_
