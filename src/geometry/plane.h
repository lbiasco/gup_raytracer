#ifndef GEOMETRY_PLANE_H_
#define GEOMETRY_PLANE_H_

#include "geometry/geometry.h"
#include "utilities/ray.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Plane impementation of the Geometry object
class Plane: public Geometry {
    public:
        // Constructors, destructors
        Plane();
        Plane(const Vector3D& p, const Vector3D& n);
        Plane(const Plane& plane);

        Plane& operator= (const Plane& rhs);

        void normal(const Vector3D& n)  { _normal = n; }
        Vector3D normal() const         { return _normal; }

        void point(const Vector3D& a)  { _point = a; }
        Vector3D point() const         { return _point; }

        Plane* Clone() const override;
        Vector3D GetNormal(const Vector3D& p) override;
        bool Hit(const Ray& ray, double& tmin, ShadeRec& sr, bool skipNormal=false) const override;
        // Pdf and Sample are nonsense functions atm since they are only used by AreaLight, 
        // which isn't supported with Plane geometry
        float Pdf(ShadeRec& sr) override;
        Vector3D Sample() override;


    private:
        static const double kEpsilon;

        Vector3D  _normal;  // Normal of the plane
        Vector3D  _point;   // Point through which plane passes 
};

#endif  // GEOMETRY_PLANE_H_
