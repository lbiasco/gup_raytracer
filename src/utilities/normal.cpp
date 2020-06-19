// This file contains the defintion of the class Normal

#include <math.h>

#include "utilities/normal.h"


// ---------------------------------------------------------- default constructor

Normal::Normal(void)
	 : x_(0.0), y_(0.0), z_(0.0)							
{}


// ---------------------------------------------------------- constructor

Normal::Normal(double a)
	 : x_(a), y_(a), z_(a)							
{}


// ---------------------------------------------------------- constructor

Normal::Normal(double x, double y, double z)	 
	: x_(x), y_(y), z_(z)
{}


// ---------------------------------------------------------- copy constructor

Normal::Normal(const Normal& n)
	: x_(n.x_), y_(n.y_), z_(n.z_)
{}


// ---------------------------------------------------------- constructor
// construct a normal from a vector

Normal::Normal(const Vector3D& v)	 
	: x_(v.x_), y_(v.y_), z_(v.z_)  
{}


// ---------------------------------------------------------- destructor

Normal::~Normal (void) 							
{}


// ----------------------------------------------------------- operator=
// assignment operator

Normal& 
Normal::operator= (const Normal& rhs) {
	if (this == &rhs)
		return (*this);

	x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_;

	return (*this);
}


// ------------------------------------------------------------ operator=
// assignment of a vector to a normal

Normal& 
Normal::operator= (const Vector3D& rhs) {
	x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_;
	return (*this);
}


// ------------------------------------------------------------ operator=
// assignment of a point to a normal

Normal& 
Normal::operator= (const Point3D& rhs) {		
	x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_;
	return (*this);
}


// ------------------------------------------------------------ normalize

void 													
Normal::Normalize(void) {	
	double length = sqrt(x_ * x_ + y_ * y_ + z_ * z_);
	x_ /= length; y_ /= length; z_ /= length;
}


// non-member function definition

// ---------------------------------------------------------- operator*
// multiplication by a matrix on the left

// a normal is transformed by multiplying it on the left by the transpose of the upper left 3 x 3
// partition of the inverse transformation matrix

Normal 											
operator* (const Matrix& mat, const Normal& n) {
	return (Normal(	mat.m_[0][0] * n.x_ + mat.m_[1][0] * n.y_ + mat.m_[2][0] * n.z_,
					mat.m_[0][1] * n.x_ + mat.m_[1][1] * n.y_ + mat.m_[2][1] * n.z_,
					mat.m_[0][2] * n.x_ + mat.m_[1][2] * n.y_ + mat.m_[2][2] * n.z_));
}
