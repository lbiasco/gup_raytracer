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
    Sphere();
    Sphere(Point3D center, double r);
    Sphere(const Sphere& sphere);

    Sphere& operator= (const Sphere& sphere);

    void center(const Point3D& c)             { center_ = c; }
    void center(double x, double y, double z) { center_ = Point3D(x, y, z); }
    Point3D center() const                    { return center_; }

    void radius(double r) { radius_ = r; }
    double radius() const { return radius_; }

    Sphere* Clone() const override;
    bool Hit(const Ray& ray, double& t, ShadeRec& s) const override;	
    
  private:
    Point3D center_;  // center coordinates as a point
    double  radius_;  // the radius 
};

#endif  // GEOMETRY_SPHERE_H_
