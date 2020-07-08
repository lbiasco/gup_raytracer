#ifndef UTILITIES_RAY_H_
#define UTILITIES_RAY_H_

#include "utilities/point.h"
#include "utilities/vector.h"

class Ray {
  public:
    Ray(void);			
    Ray(const Point3D& origin, const Vector3D& dir);
    Ray(const Ray& ray);
    ~Ray(void);	

    Ray& operator= (const Ray& rhs);

    Point3D   o_; // origin 
    Vector3D  d_; // direction 
};

#endif  // UTILITIES_RAY_H_
