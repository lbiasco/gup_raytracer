#ifndef CAMERAS_CAMERA_H_
#define CAMERAS_CAMERA_H_

#include "utilities/point.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// Base class for Camera objects
class Camera 
{
  public:
    // Constructors, destructors
    Camera(Point3D eye, Point3D lookat, Vector3D up=Vector3D(0, 1, 0));

    // Accessors, mutators
    void exposure(float value)  { exposure_ = value; }
    float exposure() const      { return exposure_; }

    void eye(Point3D point) { eye_ = point; }
    Point3D eye() const     { return eye_; }

    void lookat(Point3D point)  { lookat_ = point; }
    Point3D lookat() const      { return lookat_; }

    void up(Vector3D vector)  { up_ = vector; }
    Vector3D up() const       { return up_; }

    Vector3D u() const  { return u_; }
    Vector3D v() const  { return v_; }
    Vector3D w() const  { return w_; }

    // Functions
    void ComputeUVW(void);
    virtual void RenderScene(World& w) = 0;

  private:
    float exposure_ = 1.0;  // Used further in Ch28
    Point3D eye_;
    Point3D lookat_;
    Vector3D up_;
    Vector3D u_, v_, w_;
};

#endif  // CAMERAS_CAMERA_H_
