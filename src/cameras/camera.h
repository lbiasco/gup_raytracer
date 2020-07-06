// This is the declaration of the base class Camera

#ifndef CAMERAS_CAMERA_H_
#define CAMERAS_CAMERA_H_

#include "utilities/point.h"
#include "utilities/vector.h"

class World;

class Camera {
	public:
		Camera(Point3D eye, Point3D lookat, Vector3D up);

        Camera(Point3D eye, Point3D lookat);

		virtual
		~Camera(void);

        void
        ComputeUVW(void);

		virtual void
		RenderScene(World& w) = 0;

	public:
        Point3D eye_;
        Point3D lookat_;
        Vector3D up_;
        Vector3D u_, v_, w_;
        float exposure_ = 1.0;  // Used further in Ch28
};

#endif  // CAMERAS_CAMERA_H_
