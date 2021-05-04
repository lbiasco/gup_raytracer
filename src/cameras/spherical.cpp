#include "cameras/spherical.h"

#include <tgmath.h>

#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"
#include "world/view_plane.h"
#include "world/world.h"

Spherical::Spherical(Point3D eye, Vector3D viewDir, Vector3D up) 
    : Camera(eye, viewDir, up) {}

Spherical::Spherical(Point3D eye, Vector3D viewDir) 
    : Camera(eye, viewDir) {}

Spherical::Spherical(Point3D eye, Point3D lookat, Vector3D up) 
    : Camera(eye, lookat, up) {}

Spherical::Spherical(Point3D eye, Point3D lookat) 
    : Camera(eye, lookat) {}

Vector3D Spherical::RayDirection(const Point2D& pp, int hres, int vres, float s) const {
    // compute the normalized device coordinates
    Point2D pn(2.0 / (s * hres) * pp.x, 2.0 / (s * vres) * pp.y);

    // compute the angles lambda and phi in radians
    float lambda  = pn.x * _lambdaMax * kPiOver180;
    float psi     = pn.y * _psiMax * kPiOver180;

    // compute the spherical azimuth and polar angles
    float phi   = kPi - lambda;
    float theta = 0.5 * kPi - psi;

    float sinPhi   = std::sin(phi);
    float cosPhi   = std::cos(phi);
    float sinTheta = std::sin(theta);
    float cosTheta = std::cos(theta);

    Vector3D dir = sinTheta * sinPhi * u() + cosTheta * v() + sinTheta * cosPhi * w();
    return dir;
}


void Spherical::RenderScene(World& world) {
    RGBColor L;
    ViewPlane vp(world.viewPlane());
    double s = vp.pixelScale();
    Ray ray;
    int depth = 0;  // recursion depth

    Point2D sp;     // sample point in [0,1]x[0,1]
    Point2D pp;     // sample point on a pixel with view plane depth

    ray.origin(eye());

    for (int r = 0; r < vp.vres(); r++) {        // up
        for (int c = 0; c < vp.hres(); c++) {    // across
            L = kBlack;

            for (int j = 0; j < vp.numSamples(); j++) {
                sp = vp.samplerPtr()->SampleUnitSquare();
                pp.x = s * (c - 0.5 * vp.hres() + sp.x);
                pp.y = s * (r - 0.5 * vp.vres() + sp.y);
                ray.dir(RayDirection(pp, vp.hres(), vp.vres(), s));

                L += world.tracerPtr()->TraceRay(ray, depth);
            }

            L /= vp.numSamples();    // Average the colors
            L *= exposure();
            world.DisplayPixel(r, c, L);
        }
    }
}
