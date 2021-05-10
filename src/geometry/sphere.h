#ifndef GEOMETRY_SPHERE_H_
#define GEOMETRY_SPHERE_H_

#include "geometry/geometry.h"
#include "utilities/ray.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Sphere impementation of the Geometry object
class Sphere: public Geometry {
    public:
        // Constructors, destructors
        Sphere();
        Sphere(Vector3D center, double r);
        Sphere(const Sphere& sphere);

        Sphere& operator= (const Sphere& sphere);

        void center(const Vector3D& c)             { _center = c; }
        void center(double x, double y, double z) { _center = Vector3D(x, y, z); }
        Vector3D center() const                    { return _center; }

        void radius(double r) { _radius = r; }
        double radius() const { return _radius; }

        Sphere* Clone() const override;
        bool Hit(const Ray& ray, double& t, ShadeRec& s, bool skipNormal=false) const override;	
        
    private:
        static const double kEpsilon;

        Vector3D _center;  // center coordinates as a point
        double  _radius;  // the radius 
};

#endif  // GEOMETRY_SPHERE_H_
