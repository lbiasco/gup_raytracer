#ifndef GEOMETRY_PLANE_H_
#define GEOMETRY_PLANE_H_

#include "geometry/geometry.h"
#include "utilities/normal.h"
#include "utilities/point.h"
#include "utilities/ray.h"
#include "utilities/shade_rec.h"

// Plane impementation of the Geometry object
class Plane: public Geometry {
  public:
    // Constructors, destructors
    Plane(void);
    Plane(const Point3D& point, const Normal& normal);
    Plane(const Plane& plane);
    ~Plane(void) override;

    Plane& operator= (const Plane& rhs);

    void SetNormal(const Normal& n);
    void SetPoint(const Point3D& a);

    Plane* Clone(void) const override;
    bool Hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
    
  private:
    Point3D 	a_;   // Point through which plane passes 
    Normal 		n_;   // Normal of the plane
};

inline void Plane::SetNormal(const Normal& n) {
  n_ = n;
}

inline void Plane::SetPoint(const Point3D& a) {
  a_ = a;
}

#endif  // GEOMETRY_PLANE_H_
