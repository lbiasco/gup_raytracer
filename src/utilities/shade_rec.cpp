// there is no default constructor as the World reference always has to be initialised
// there is also no assignment operator as we don't want to assign the world
// the copy constructor only copies the world reference
// the ray tracer is written so that new ShadeRec objects are always constructed
// using the first constructor or the copy constructor

#include "utilities/shade_rec.h"

#include "utilities/constants.h"

ShadeRec::ShadeRec(World& wr) 
    :   hitAnObject(false),
        localHitPoint(),
        normal(),
        color(kBlack),
        w(wr) {}

ShadeRec::ShadeRec(const ShadeRec& sr)
    :   hitAnObject(sr.hitAnObject),
        localHitPoint(sr.localHitPoint),
        color(sr.color),
        w(sr.w) {}
