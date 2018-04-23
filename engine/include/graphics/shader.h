#pragma once

// Library includes
#include "resource/shaderfilehandler.h"
#include "recipe/topping_descriptor.h"

// STL includes
#include <vector>

 namespace donut
 {
 	// Basic shader (this does mean that we do not replace the default gl pipeline)
	#define BASIC_SHADER -1

 	// Flags for shader compilation
 	#define VERTEX_FLAG 0x0001
 	#define TESS_CONTROL_FLAG 0x0002
 	#define TESS_EVAL_FLAG 0x0004
 	#define GEOMETRY_FLAG 0x0008
 	#define FRAGMENT_FLAG 0x0010
 }