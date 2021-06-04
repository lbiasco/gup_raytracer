#ifndef GEOMETRY_RECTANGLE_H_
#define GEOMETRY_RECTANGLE_H_

#include "geometry/geometry.h"
#include "utilities/ray.h"
#include "utilities/shade_rec.h"
#include "utilities/vector.h"

// Rect impementation of the Geometry object
class Rect: public Geometry {
    public:
        // Constructors, destructors
        Rect();
        Rect(const Vector3D& p, const Vector3D& a, const Vector3D& b);
        Rect(const Rect& rect);

        Rect& operator= (const Rect& rhs);

        void point(const Vector3D& p) { _point = p; }
        Vector3D point() const { return _point; }

        void sideA(const Vector3D& a);
        Vector3D sideA() const { return _sideA; }

        void sideB(const Vector3D& b);
        Vector3D sideB() const { return _sideB; }

        void flipNormal(bool v);
        bool flipNormal() const { return _flipNormal; } 

        Rect* Clone() const override;
        Vector3D GetNormal(const Vector3D& p) override;
        bool Hit(const Ray& ray, double& tmin, ShadeRec& sr, bool skipNormal=false) const override;
        float Pdf(ShadeRec& sr) override;
        Vector3D Sample() override;


    private:
        static const double kEpsilon;

        Vector3D _sideA;    // one leg of the rectangle
        Vector3D _sideB;    // other leg of the rectangle
        Vector3D _point;    // starting corner of the rectangle (rhombus)
        bool _flipNormal;   // flip normal (which is automatically determined by A x B)

        float _areaInv;
        Vector3D _normal;
        
        void _RecalculateMembers();
};

#endif  // GEOMETRY_RECTANGLE_H_
