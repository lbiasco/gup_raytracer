#include "geometry/rectangle.h"

const double Rect::kEpsilon = 0.0001;

Rect::Rect(void) : Geometry(), _point(0.0), _sideA(1, 0, 0), _sideB(0, 1, 0) {
    _RecalculateMembers();
}

Rect::Rect(const Vector3D& p, const Vector3D& a, const Vector3D& b) 
    : Geometry(), _point(p), _sideA(a), _sideB(b) {
    _RecalculateMembers();
}

Rect::Rect(const Rect& rect) 
    : Geometry(rect), _point(rect._point), _sideA(rect._sideA), _sideB(rect._sideB) {
    _RecalculateMembers();
}

Rect& Rect::operator= (const Rect& rhs) {
    if (this == &rhs)
        return (*this);

    Geometry::operator= (rhs);
    _point = rhs._point;
    _sideA = rhs._sideA;
    _sideB = rhs._sideB;
    _RecalculateMembers();
    return *this;
}

void Rect::sideA(const Vector3D& a) {
    _sideA = a;
    _RecalculateMembers();
}

void Rect::sideB(const Vector3D& b) {
    _sideB = b;
    _RecalculateMembers();
}

void Rect::flipNormal(bool v) {
    _flipNormal = v;
    _RecalculateMembers();
}

Rect* Rect::Clone(void) const {
    return (new Rect(*this));
}

Vector3D Rect::GetNormal(const Vector3D& p) {
    return _normal;
}

bool Rect::Hit(const Ray& ray, double& tmin, ShadeRec& sr, bool skipNormal) const {	
    float t = (_point - ray.origin()) * _normal / (ray.dir() * _normal); 

    if (t > kEpsilon) {
        Vector3D planeHitPoint = ray.origin() + t * ray.dir();
        Vector3D pointToHitPoint = planeHitPoint - _point;

        float aDotHit = _sideA * pointToHitPoint;
        float bDotHit = _sideB * pointToHitPoint;

        if (aDotHit > 0 && aDotHit < _sideA.LengthSquared() && 
                bDotHit > 0 && bDotHit < _sideB.LengthSquared()) {
            tmin = t;
            sr.localHitPoint = planeHitPoint;
            if (!skipNormal) {
                sr.normal = _normal;
            }
            return true;
        }
    }
    return false;
}

float Rect::Pdf(ShadeRec& sr) {
    return _areaInv;
}

Vector3D Rect::Sample() {
    Vector2D samplePoint = _samplerPtr->SampleUnitSquare();
    return (_point + samplePoint.x * _sideA + samplePoint.y * _sideB);
}

void Rect::_RecalculateMembers() {
    _areaInv = 1 / (_sideA.Length() * _sideB.Length());

    if (_flipNormal) {
        _normal = _sideB ^ _sideA;
    } else {
        _normal = _sideA ^ _sideB;
    }
    _normal.Normalize();
}
