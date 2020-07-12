#ifndef GEOMETRY_PLANE_H_
#define GEOMETRY_PLANE_H_

#include "geometry/geometry.h"
#include "utilities/point.h"
#include "utilities/ray.h"
#include "utilities/shade_rec.h"

// Plane impementation of the Geometry object
class Plane: public Geometry {
  public:
    // Constructors, destructors
    Plane();
    Plane(const Point3D& p, const Vector3D& n);
    Plane(const Plane& plane);

    Plane& operator= (const Plane& rhs);

    void normal(const Vector3D& n)  { normal_ = n; }
    Vector3D normal() const         { return normal_; }

    void point(const Point3D& a)  { point_ = a; }
    Point3D point() const         { return point_; }

    Plane* Clone() const override;
    bool Hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
    
  private:
    Vector3D  normal_;  // Normal of the plane
    Point3D   point_;   // Point through which plane passes 
};

#endif  // GEOMETRY_PLANE_H_
