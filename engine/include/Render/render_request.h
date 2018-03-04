#pragma once

// Library includes
#include "resource/types.h"
#include "graphics/uniformhandler.h"

// Bento includes
#include <bento_math/types.h>

// External includes
#include <map>

namespace donut
{
	// This structure encapsulates everything that is required to draw a geometry with a material in a given scene
	struct TRenderRequest
	{
		// Instance data
		TOPPING_GUID topping;
		GEOMETRY_GUID geometry;

		// Mesh transform
		bento::Matrix4 transform;
	};

	// Processed a render request (draw it to the screen)
	void ProcessRenderRequest(const TRenderRequest& _request, std::map<STRING_TYPE, TUniformHandler>& _uniforms);
}