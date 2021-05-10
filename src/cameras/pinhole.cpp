#include "cameras/pinhole.h"

#include <tgmath.h>

#include "samplers/sampler.h"
#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

Pinhole::Pinhole(Vector3D eye, Vector3D viewDir, Vector3D up, int fov) 
    : Camera(eye, viewDir, up), _fov(fov) {}

Pinhole::Pinhole(Vector3D eye, Vector3D viewDir, int fov) 
    : Camera(eye, viewDir), _fov(fov) {}

double Pinhole::ComputePlaneDepth(World& w) const {
    int fov = std::max(1, std::min(_fov, 179)); // Lock fov to 1-179 for now
    double halfWidth = w.viewPlane().hres() * w.viewPlane().pixelScale() * 0.5; // Multiply by s to maintain fov across resolutions
    return halfWidth / std::tan(fov * 0.5 * kPiOver180);
}

Vector3D Pinhole::RayDirection(const Vector3D& p) const {
    Vector3D dir = p.x * u() + p.y * v() - p.z * w();
    dir.Normalize();
    return dir;
}

void Pinhole::RenderScene(World& world) {
    RGBColor L;
    ViewPlane vp(world.viewPlane());
    double s = vp.pixelScale();
    Ray ray;
    int depth = 0;          // recursion depth
    Vector2D sp;             // sample point in [0,1]x[0,1]
    Vector3D pp;             // sample point on a pixel with view plane depth

    pp.z = ComputePlaneDepth(world);
    s /= _zoom;
    ray.origin(eye());

    for (int r = 0; r < vp.vres(); r++) {        // up
        for (int c = 0; c < vp.hres(); c++) {    // across
            L = kBlack;

            for (int j = 0; j < vp.numSamples(); j++) {
                sp = vp.samplerPtr()->SampleUnitSquare();
                pp.x = s * (c - 0.5 * vp.hres() + sp.x) + _apertureOffsetX;
                pp.y = s * (r - 0.5 * vp.vres() + sp.y) + _apertureOffsetY;
                ray.dir(RayDirection(pp));
                L += world.tracerPtr()->TraceRay(ray, depth);
            }

            L /= vp.numSamples();    // Average the colors
            L *= exposure();
            world.DisplayPixel(r, c, L);
        }
    }
}
