#ifndef UTILITIES_RAY_H_
#define UTILITIES_RAY_H_

#include "utilities/vector.h"

class Ray {
    public:
        Ray() : _origin(0.0), _dir(0.0, 0.0, 1.0) {}			
        Ray(const Vector3D& o, const Vector3D& d) : _origin(o), _dir(d) {}
        Ray(const Ray& ray) : _origin(ray._origin), _dir(ray._dir) {}

        Ray& operator= (const Ray& rhs);

        void origin(Vector3D o) { _origin = o; }
        Vector3D origin() const { return _origin; }

        void dir(Vector3D d) { _dir = d; }
        Vector3D dir() const { return _dir; }

    private:
        Vector3D  _origin; // origin 
        Vector3D  _dir; // direction
};

#endif  // UTILITIES_RAY_H_
