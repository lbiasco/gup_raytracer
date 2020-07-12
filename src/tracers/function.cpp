#include "tracers/function.h"

#include "world/world.h"

Function::Function(void) : Tracer() {}

Function::Function(World* world_ptr) : Tracer(world_ptr) {}
