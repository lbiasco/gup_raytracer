#ifndef UTILITIES_POINT_3D_H_
#define UTILITIES_POINT_3D_H_

// This file contains the declaration of the class Point3D

#include "utilities/matrix.h"
#include "utilities/vector_3d.h"

class Point3D {
	public:
	
		double x_, y_, z_;
	
		Point3D();													// default constructor
		Point3D(const double c);									// constructor
		Point3D(const double x, const double y, const double z);	// constructor
		Point3D(const Point3D& p);									// copy constructor
		~Point3D();													// destructor
		
		Point3D& 													// assignment operator
		operator= (const Point3D& p);
		
		Point3D 													// unary minus
		operator- (void) const;
	
		Vector3D 													// vector joining two points
		operator- (const Point3D& p) const;
		
		Point3D 													// addition of a vector				
		operator+ (const Vector3D& v) const;
		
		Point3D 													// subtraction of a vector
		operator- (const Vector3D& v) const;
				
		Point3D 													// multiplication by a double on the right
		operator* (const double a) const;
		
		double														// square of distance bertween two points
		DistanceSquared(const Point3D& p) const;
		
		double														// distance between two points
		Distance(const Point3D& p) const;
};



// inlined member functions

// -------------------------------------------------------------- operator-
// unary minus

inline Point3D 
Point3D::operator- (void) const {
	return (Point3D(-x_, -y_, -z_));
}


// -------------------------------------------------------------- operator-
// the vector that joins two points

inline Vector3D 
Point3D::operator- (const Point3D& p) const {
	return (Vector3D(x_ - p.x_,y_ - p.y_,z_ - p.z_));
}


// -------------------------------------------------------------- operator+
// addition of a vector to a point that returns a new point

inline Point3D 
Point3D::operator+ (const Vector3D& v) const {
	return (Point3D(x_ + v.x_, y_ + v.y_, z_ + v.z_));
}


// -------------------------------------------------------------- operator-
// subtraction of a vector from a point that returns a new point

inline Point3D 
Point3D::operator- (const Vector3D& v) const {
	return (Point3D(x_ - v.x_, y_ - v.y_, z_ - v.z_));
}


// -------------------------------------------------------------- operator*
// mutliplication by a double on the right

inline Point3D 
Point3D::operator* (const double a) const {
	return (Point3D(x_ * a, y_ * a, z_ * a));
}


// -------------------------------------------------------------- DistanceSquared
// the square of the distance between the two points as a member function

inline double
Point3D::DistanceSquared(const Point3D& p) const {
	return (	(x_ - p.x_) * (x_ - p.x_) 
			+ 	(y_ - p.y_) * (y_ - p.y_)
			+	(z_ - p.z_) * (z_ - p.z_) );
}


// inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a double on the left

Point3D
operator* (double a, const Point3D& p);

inline Point3D
operator* (double a, const Point3D& p) {
	return (Point3D(a * p.x_, a * p.y_, a * p.z_));
}


// non-inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a matrix on the left

Point3D 						
operator* (const Matrix& mat, const Point3D& p);

#endif  // UTILITIES_POINT_3D_H_
