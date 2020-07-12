// The tracer classes have no copy constructor, assignment operator. or clone function because 
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#ifndef TRACERS_TRACER_H_
#define TRACERS_TRACER_H_

#include "utilities/constants.h"
#include "utilities/ray.h"
#include "utilities/rgb_color.h"

// Forward declarations
class World;

// Base class for Tracer objects
class Tracer {
  public:
    // Constructors, destructors
    Tracer();
    Tracer(World* world_ptr);
    virtual	~Tracer();

    void world_ptr(World *ptr)  { world_ptr_ = ptr; }
    World* world_ptr() const    { return world_ptr_; }

    virtual RGBColor TraceRay(const Ray& ray) const;

    virtual RGBColor TraceRay(const Ray ray, const int depth) const;

  private:
    World* world_ptr_;
};

#endif  // TRACERS_TRACER_H_
