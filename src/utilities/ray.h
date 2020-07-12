#ifndef UTILITIES_RAY_H_
#define UTILITIES_RAY_H_

#include "utilities/point.h"
#include "utilities/vector.h"

class Ray {
  public:
    Ray() : origin_(0.0), dir_(0.0, 0.0, 1.0) {}			
    Ray(const Point3D& o, const Vector3D& d) : origin_(o), dir_(d) {}
    Ray(const Ray& ray) : origin_(ray.origin_), dir_(ray.dir_) {}

    Ray& operator= (const Ray& rhs);

    void origin(Point3D o) { origin_ = o; }
    Point3D origin() const { return origin_; }

    void dir(Vector3D d) { dir_ = d; }
    Vector3D dir() const { return dir_; }

  private:
    Point3D   origin_; // origin 
    Vector3D  dir_; // direction
};

#endif  // UTILITIES_RAY_H_
