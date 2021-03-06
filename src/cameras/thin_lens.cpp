#include "cameras/thin_lens.h"

#include <tgmath.h>

#include "samplers/sampler.h"
#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

ThinLens::ThinLens(Vector3D eye, Vector3D viewDir, Vector3D up) 
    : Pinhole(eye, viewDir, up) {}

ThinLens::ThinLens(Vector3D eye, Vector3D viewDir) 
    : Pinhole(eye, viewDir) {}

void ThinLens::samplerPtr(Sampler* sp) {
    if (_samplerPtr) {
        delete _samplerPtr;
        _samplerPtr = NULL;
    }
    _samplerPtr = sp;
    _samplerPtr->MapSamplesToUnitDisk();
}

Vector3D ThinLens::RayDirection(const Vector3D& pixelPoint, const Vector2D& lensPoint) const {
    Vector2D p;  // hit point on focal plane
    p.x = pixelPoint.x * _focalLength / pixelPoint.z;
    p.y = pixelPoint.y * _focalLength / pixelPoint.z;

    Vector3D dir = (p.x - lensPoint.x) * u() + 
                (p.y - lensPoint.y) * v() - _focalLength * w();
    dir.Normalize();
    return dir;
}

void ThinLens::RenderScene(World& world) {
    RGBColor L;
    ViewPlane vp(world.viewPlane());
    double s = vp.pixelScale();
    Ray ray;
    int depth = 0;  // recursion depth

    Vector2D sp;     // sample point in [0,1]x[0,1]
    Vector3D pp;     // sample point on a pixel with view plane depth
    Vector2D dp;     // sample point on unit disk
    Vector2D lp;     // sample point on lens

    pp.z = ComputePlaneDepth(world);
    s /= zoom();

    for (int r = 0; r < vp.vres(); r++) {        // up
        for (int c = 0; c < vp.hres(); c++) {    // across
            L = kBlack;

            for (int j = 0; j < vp.numSamples(); j++) {
                sp = vp.samplerPtr()->SampleUnitSquare();
                pp.x = s * (c - 0.5 * vp.hres() + sp.x) + apertureOffsetX();
                pp.y = s * (r - 0.5 * vp.vres() + sp.y) + apertureOffsetY();

                dp = _samplerPtr->SampleUnitDisk();
                lp = dp * _lensRadius;

                ray.origin(eye() + lp.x * u() + lp.y * v());
                ray.dir(RayDirection(pp, lp));
                L += world.tracerPtr()->TraceRay(ray, depth);
            }

            L /= vp.numSamples();    // Average the colors
            L *= exposure();
            world.DisplayPixel(r, c, L);
        }
    }
}
