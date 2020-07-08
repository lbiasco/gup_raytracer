#ifndef GEOMETRY_SPHERE_H_
#define GEOMETRY_SPHERE_H_

#include "geometry/geometry.h"
#include "utilities/point.h"
#include "utilities/ray.h"
#include "utilities/shade_rec.h"

// Sphere impementation of the Geometry object
class Sphere: public Geometry {
  public:
    // Constructors, destructors
    Sphere(void);
    Sphere(Point3D center, double r);
    Sphere(const Sphere& sphere);
    ~Sphere(void) override;

    Sphere& operator= (const Sphere& sphere);

    void SetCenter(const Point3D& c);
    void SetCenter(const double x, const double y, const double z);
    void SetRadius(const double r);

    Sphere* Clone(void) const override;
    bool Hit(const Ray& ray, double& t, ShadeRec& s) const override;	
    
  private:
    Point3D center_;  // center coordinates as a point
    double  radius_;  // the radius 
};

inline void Sphere::SetCenter(const Point3D& c) {
  center_ = c;
}

inline void Sphere::SetCenter(const double x, const double y, const double z) {
  center_.x_ = x;
  center_.y_ = y;
  center_.z_ = z;
}

inline void Sphere::SetRadius(const double r) {
  radius_ = r;
}

#endif  // GEOMETRY_SPHERE_H_
