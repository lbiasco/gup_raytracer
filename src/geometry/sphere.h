#ifndef GEOMETRY_SPHERE_H_
#define GEOMETRY_SPHERE_H_

// This file contains the declaration of the class Sphere

#include "geometry/geometry.h"

//-------------------------------------------------------------------------------- class Sphere

class Sphere: public Geometry {	
								  	
	public:
		
		Sphere(void);   									// Default constructor
				
		Sphere(Point3D center, double r);					// Constructor 
					
		Sphere(const Sphere& sphere); 						// Copy constructor
		
		virtual Sphere* 									// Virtual copy constructor
		Clone(void) const;

		virtual												// Destructor
		~Sphere(void);   									

		Sphere& 											// assignment operator
		operator= (const Sphere& sphere);				
																					
		void
		SetCenter(const Point3D& c);
		
		void
		SetCenter(const double x, const double y, const double z);
		
		void
		SetRadius(const double r);
						
		virtual bool 												 
		Hit(const Ray& ray, double& t, ShadeRec& s) const;	
		
	private:
	
		Point3D 	center_;   			// center coordinates as a point  
		double 		radius_;				// the radius 
		
		static const double kEpsilon;   // for shadows and secondary rays
};



inline void
Sphere::SetCenter(const Point3D& c) {
	center_ = c;
}
		
inline void
Sphere::SetCenter(const double x, const double y, const double z) {
	center_.x_ = x;
	center_.y_ = y;
	center_.z_ = z;
}
		
inline void
Sphere::SetRadius(const double r) {
	radius_ = r;
}

#endif  // GEOMETRY_SPHERE_H_
