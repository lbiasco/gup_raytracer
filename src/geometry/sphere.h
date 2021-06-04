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

        void radius(double r);
        double radius() const { return _radius; }

        void samplerPtr(Sampler* ptr) override;

        Sphere* Clone() const override;
        Vector3D GetNormal(const Vector3D& p) override;
        bool Hit(const Ray& ray, double& t, ShadeRec& s, bool skipNormal=false) const override;
        float Pdf(ShadeRec& sr) override;
        Vector3D Sample() override;

        
    private:
        static const double kEpsilon;

        Vector3D _center;   // center coordinates as a point
        double _radius;     // the radius 
        float _areaInv;     // inverse area to efficiently return Pdf

        void _CalculateAreaInv();
};

#endif  // GEOMETRY_SPHERE_H_
