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
    virtual ~Camera(void);

    void ComputeUVW(void);
    virtual void RenderScene(World& w) = 0;

  protected:
    Point3D eye_;
    Point3D lookat_;
    Vector3D up_;
    Vector3D u_, v_, w_;
    float exposure_ = 1.0;  // Used further in Ch28
};

#endif  // CAMERAS_CAMERA_H_
