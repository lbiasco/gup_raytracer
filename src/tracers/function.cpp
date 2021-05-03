#include "tracers/function.h"

#include "world/world.h"

Function::Function(void) : Tracer() {}

Function::Function(World* worldPtr) : Tracer(worldPtr) {}
