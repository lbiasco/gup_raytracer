#ifndef UTILITIES_RAY_H_
#define UTILITIES_RAY_H_

#include "utilities/point_3d.h"
#include "utilities/vector_3d.h"

class Ray {
	public:
	
		Point3D     o_;  	// origin 
		Vector3D    d_; 		// direction 
		
		Ray(void);			
		
		Ray(const Point3D& origin, const Vector3D& dir);	
		
		Ray(const Ray& ray); 		
		
		Ray& 						
		operator= (const Ray& rhs);
		 								
		~Ray(void);
};

#endif  // UTILITIES_RAY_H_
