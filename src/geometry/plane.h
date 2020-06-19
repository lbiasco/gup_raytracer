#ifndef GEOMETRY_PLANE_H_
#define GEOMETRY_PLANE_H_

#include "geometry/geometry.h"

//-------------------------------------------------------------------- class Plane

class Plane: public Geometry {
	
	public:
	
		Plane(void);   												// default constructor
		
		Plane(const Point3D& point, const Normal& normal);			// constructor	
	
		Plane(const Plane& plane); 									// copy constructor
		
		virtual Plane* 												// virtual copy constructor
		Clone(void) const;

		Plane& 														// assignment operator
		operator= (const Plane& rhs);	
		
		virtual														// destructor
		~Plane(void);   											
					
		virtual bool 																								 
		Hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
		
	private:
	
		Point3D 	a_;   				// point through which plane passes 
		Normal 		n_;					// normal to the plane
				
		static const double kEpsilon;   // for shadows and secondary rays
};

#endif  // GEOMETRY_PLANE_H_
