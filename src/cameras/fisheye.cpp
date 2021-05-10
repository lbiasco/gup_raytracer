#include "cameras/fisheye.h"

#include <tgmath.h>

#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

Fisheye::Fisheye(Vector3D eye, Vector3D viewDir, Vector3D up) 
    : Camera(eye, viewDir, up) {}

Fisheye::Fisheye(Vector3D eye, Vector3D viewDir) 
    : Camera(eye, viewDir) {}

Vector3D Fisheye::RayDirection(const Vector2D& pp, int hres, int vres, float s, float& rSq) const {
    // compute the normalized device coordinates
    Vector2D pn(2.0 / (s * hres) * pp.x, 2.0 / (s * vres) * pp.y);
    rSq = pn.x * pn.x + pn.y * pn.y;

    if (rSq <= 1.0) {
        float r = sqrt(rSq);
        float psi = r * _psiMax * kPiOver180;
        float sinPsi = std::sin(psi);
        float cosPsi = std::cos(psi);
        float sinAlpha = pn.y / r;
        float cosAlpha = pn.x / r;
        Vector3D dir = sinPsi * cosAlpha * u() + sinPsi * sinAlpha * v() - cosPsi * w();

        return dir;
    } else
    {
        return Vector3D(0.0);
    }
}


void Fisheye::RenderScene(World& world) {
    RGBColor L;
    ViewPlane vp(world.viewPlane());
    double s = vp.pixelScale();
    Ray ray;
    int depth = 0;  // recursion depth

    Vector2D sp;     // sample point in [0,1]x[0,1]
    Vector2D pp;     // sample point on a pixel with view plane depth
    float rSq;     // sum of squares of normalized device coordinates

    ray.origin(eye());

    for (int r = 0; r < vp.vres(); r++) {        // up
        for (int c = 0; c < vp.hres(); c++) {    // across
            L = kBlack;

            for (int j = 0; j < vp.numSamples(); j++) {
                sp = vp.samplerPtr()->SampleUnitSquare();
                pp.x = s * (c - 0.5 * vp.hres() + sp.x);
                pp.y = s * (r - 0.5 * vp.vres() + sp.y);
                ray.dir(RayDirection(pp, vp.hres(), vp.vres(), s, rSq));

                if (rSq <= 1.0)
                L += world.tracerPtr()->TraceRay(ray, depth);
            }

            L /= vp.numSamples();    // Average the colors
            L *= exposure();
            world.DisplayPixel(r, c, L);
        }
    }
}
