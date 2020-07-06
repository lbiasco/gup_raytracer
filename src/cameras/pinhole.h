// This is the declaration of the class Pinhole

#ifndef CAMERAS_PINHOLE_H_
#define CAMERAS_PINHOLE_H_

#include "cameras/camera.h"
#include "utilities/point.h"
#include "utilities/vector.h"

class World;

class Pinhole : public Camera {
	public:
		Pinhole(Point3D eye, Point3D lookat, Vector3D up, float d);

        Pinhole(Point3D eye, Point3D lookat, float d);

		virtual											
		~Pinhole(void);

        Vector3D
        RayDirection(const Point2D& p) const;

		virtual void	
		RenderScene(World& w);

	public:
        float d_;           // view-plane distance
        float zoom_ = 1.0;  // zoom factor
};

#endif  // CAMERAS_PINHOLE_H_
