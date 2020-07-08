
#ifndef UTILITIES_NORMAL_H_
#define UTILITIES_NORMAL_H_

#include "utilities/matrix.h"
#include "utilities/vector.h"
#include "utilities/point.h"

class Normal 
{	
  public:
    Normal(void);
    Normal(double a);
    Normal(double x, double y, double z);
    Normal(const Normal& n);
    Normal(const Vector3D& v);
    ~Normal(void);

    Normal& operator= (const Normal& rhs);
    Normal& operator= (const Vector3D& rhs);
    Normal& operator= (const Point3D& rhs);
    Normal operator- (void) const;
    Normal operator+ (const Normal& n) const;
    Normal& operator+= (const Normal& n);
    double operator* (const Vector3D& v) const;
    Normal operator* (const double a) const;

    void Normalize(void); 		

    double	x_, y_, z_;							 		
};

// Inline, member functions
inline Normal Normal::operator- (void) const {
  return Normal(-x_, -y_, -z_);
}

inline Normal Normal::operator+ (const Normal& n) const {
  return Normal(x_ + n.x_, y_ + n.y_, z_ + n.z_);
}

inline Normal& Normal::operator+= (const Normal& n) {
  x_ += n.x_; y_ += n.y_; z_ += n.z_;
    return *this;
}

inline double Normal::operator* (const Vector3D& v) const {
  return (x_ * v.x_ + y_ * v.y_ + z_ * v.z_);
}

inline Normal Normal::operator* (const double a) const {
  return Normal(x_ * a, y_ * a, z_ * a);
}

// Inline, non-member functions
Normal operator* (const double a, const Normal& n);
inline Normal operator*(const double f, const Normal& n) {
  return Normal(f * n.x_, f * n.y_, f * n.z_);
}

Vector3D operator+ (const Vector3D& v, const Normal& n);
inline Vector3D operator+ (const Vector3D& v, const Normal& n) {	
  return Vector3D(v.x_ + n.x_, v.y_ + n.y_, v.z_ + n.z_);
}	

Vector3D operator- (const Vector3D&, const Normal& n);
inline Vector3D operator- (const Vector3D& v, const Normal& n) {
 return Vector3D(v.x_ - n.x_, v.y_ - n.y_, v.z_ - n.z_);
}

double operator* (const Vector3D& v, const Normal& n);
inline double operator* (const Vector3D& v, const Normal& n) {
  return (v.x_ * n.x_ + v.y_ * n.y_ + v.z_ * n.z_);     
}

// Non-inline, non-member functions
Normal operator* (const Matrix& mat, const Normal& n);

#endif  // UTILITIES_NORMAL_H_
