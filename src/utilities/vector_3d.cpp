// This file contains the definition of the class Vector3D

#include <math.h>

#include "utilities/vector_3d.h"
#include "utilities/normal.h"
#include "utilities/point_3d.h"

// ---------------------------------------------------------- default constructor

Vector3D::Vector3D(void)
	 : x_(0.0), y_(0.0), z_(0.0)							
{}

// ---------------------------------------------------------- constructor

Vector3D::Vector3D(double a)
	 : x_(a), y_(a), z_(a)							
{}

// ---------------------------------------------------------- constructor

Vector3D::Vector3D(double x, double y, double z)	 
	: x_(x), y_(y), z_(z)
{}

// ---------------------------------------------------------- copy constructor

Vector3D::Vector3D(const Vector3D& vector)
	: x_(vector.x_), y_(vector.y_), z_(vector.z_)
{}


// ---------------------------------------------------------- constructor
// constructs a vector from a normal

Vector3D::Vector3D(const Normal& n)	 
	: x_(n.x_), y_(n.y_), z_(n.z_)
{}

// ---------------------------------------------------------- constructor
// constructs a vector from a point
// this is used in the ConcaveHemisphere hit functions

Vector3D::Vector3D(const Point3D& p)	 
	: x_(p.x_), y_(p.y_), z_(p.z_)
{}


// ---------------------------------------------------------- destructor

Vector3D::~Vector3D (void) 							
{}


// ---------------------------------------------------------- assignment operator

Vector3D& 
Vector3D::operator= (const Vector3D& rhs) {
	if (this == &rhs)
		return (*this);

	x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_;

	return (*this);
}


// ----------------------------------------------------------- assignment operator
// assign a Normal to a vector

Vector3D& 
Vector3D::operator= (const Normal& rhs) {
	x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_;
	return (*this);
}


// ---------------------------------------------------------- assignment operator 
// assign a point to a vector

Vector3D& 												
Vector3D::operator= (const Point3D& rhs) {
	x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_;
	return (*this);
}


// ----------------------------------------------------------  Length
// length of the vector

double													
Vector3D::Length(void) {
	return (sqrt(x_ * x_ + y_ * y_ + z_ * z_));
}


// ----------------------------------------------------------  Normalize
// converts the vector to a unit vector

void 													
Vector3D::Normalize(void) {	
	double length = sqrt(x_ * x_ + y_ * y_ + z_ * z_);
	x_ /= length; y_ /= length; z_ /= length;
}


// ----------------------------------------------------------  Hat
// converts the vector to a unit vector and returns the vector

Vector3D& 													
Vector3D::Hat(void) {	
	double length = sqrt(x_ * x_ + y_ * y_ + z_ * z_);
	x_ /= length; y_ /= length; z_ /= length;
	return (*this);
} 


// non-member function

// ----------------------------------------------------------  operator* 
// multiplication by a matrix on the left

Vector3D 
operator* (const Matrix& mat, const Vector3D& v) {
	return (Point3D(mat.m_[0][0] * v.x_ + mat.m_[0][1] * v.y_ + mat.m_[0][2] * v.z_,
					mat.m_[1][0] * v.x_ + mat.m_[1][1] * v.y_ + mat.m_[1][2] * v.z_,
					mat.m_[2][0] * v.x_ + mat.m_[2][1] * v.y_ + mat.m_[2][2] * v.z_));
}
