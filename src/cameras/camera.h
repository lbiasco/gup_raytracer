#ifndef CAMERAS_CAMERA_H_
#define CAMERAS_CAMERA_H_

#include "utilities/point.h"
#include "utilities/vector.h"

// Forward declarations
class World;

// Base class for Camera objects
class Camera {
  public:
    // Constructors, destructors
    Camera(Point3D eye, Vector3D view_dir, Vector3D up=Vector3D(0, 1, 0));
    Camera(Point3D eye, Point3D lookat, Vector3D up=Vector3D(0, 1, 0));

    // Accessors, mutators
    void exposure(double value)  { exposure_ = value; }
    double exposure() const      { return exposure_; }

    void eye(Point3D p) { eye_ = p; }
    Point3D eye() const;

    void rotate_u(double degrees) { rotate_u_ = degrees; }
    double rotate_u() const { return rotate_u_; }
    void rotate_v(double degrees) { rotate_v_ = degrees; }
    double rotate_v() const { return rotate_v_; }
    void rotate_w(double degrees) { rotate_w_ = degrees; }
    double rotate_w() const { return rotate_w_; }

    void translate_u(double d) { translate_u_ = d; }
    double translate_u() const { return translate_u_; }
    void translate_v(double d) { translate_v_ = d; }
    double translate_v() const { return translate_v_; }
    void translate_w(double d) { translate_w_ = d; }
    double translate_w() const { return translate_w_; }

    void up(Vector3D v) { up_ = v; }
    Vector3D up() const { return up_; }

    void view_dir(Vector3D v) { view_dir_ = v; }
    Vector3D view_dir() const { return view_dir_; }

    Vector3D u() const  { return u_; }
    Vector3D v() const  { return v_; }
    Vector3D w() const  { return w_; }

    // Functions
    void ComputeUVW();
    void LookAt(Point3D lookat);
    virtual void RenderScene(World& w) = 0;

  private:
    void TransformUVW();

  private:
    double exposure_ = 1.0;  // Used further in Ch28
    Point3D eye_;
    double rotate_u_ = 0.0;     // Rotate around u
    double rotate_v_ = 0.0;     // Rotate around v
    double rotate_w_ = 0.0;     // Rotate around w
    double translate_u_ = 0.0;  // Translate along u
    double translate_v_ = 0.0;  // Translate along v
    double translate_w_ = 0.0;  // Translate along w
    Vector3D up_;
    Vector3D view_dir_;
    Vector3D u_, v_, w_;
};

#endif  // CAMERAS_CAMERA_H_
