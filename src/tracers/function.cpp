#include <tgmath.h>

#include "tracers/function.h"
#include "world/world.h"

// -------------------------------------------------------------------- default constructor

Function::Function(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor
		
Function::Function(World* world_ptr)
	: Tracer(world_ptr)
{}


// -------------------------------------------------------------------- destructor

Function::~Function(void) {}
