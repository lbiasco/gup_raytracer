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
    Camera(Point3D eye, Vector3D viewDir, Vector3D up=Vector3D(0, 1, 0));
    Camera(Point3D eye, Point3D lookat, Vector3D up=Vector3D(0, 1, 0));

    // Accessors, mutators
    void exposure(double value)  { _exposure = value; }
    double exposure() const      { return _exposure; }

    void eye(Point3D p) { _eye = p; }
    Point3D eye() const;

    void rotateU(double degrees) { _rotateU = degrees; }
    double rotateU() const { return _rotateU; }
    void rotateV(double degrees) { _rotateV = degrees; }
    double rotateV() const { return _rotateV; }
    void rotateW(double degrees) { _rotateW = degrees; }
    double rotateW() const { return _rotateW; }

    void translateU(double d) { _translateU = d; }
    double translateU() const { return _translateU; }
    void translateV(double d) { _translateV = d; }
    double translateV() const { return _translateV; }
    void translateW(double d) { _translateW = d; }
    double translateW() const { return _translateW; }

    void up(Vector3D v) { _up = v; }
    Vector3D up() const { return _up; }

    void viewDir(Vector3D v) { _viewDir = v; }
    Vector3D viewDir() const { return _viewDir; }

    Vector3D u() const  { return _u; }
    Vector3D v() const  { return _v; }
    Vector3D w() const  { return _w; }

    // Functions
    void ComputeUVW();
    void LookAt(Point3D lookat);
    virtual void RenderScene(World& w) = 0;

private:
    void TransformUVW();

private:
    double _exposure = 1.0;  // Used further in Ch28
    Point3D _eye;
    double _rotateU = 0.0;     // Rotate around u
    double _rotateV = 0.0;     // Rotate around v
    double _rotateW = 0.0;     // Rotate around w
    double _translateU = 0.0;  // Translate along u
    double _translateV = 0.0;  // Translate along v
    double _translateW = 0.0;  // Translate along w
    Vector3D _up;
    Vector3D _viewDir;
    Vector3D _u, _v, _w;
};

#endif  // CAMERAS_CAMERA_H_
