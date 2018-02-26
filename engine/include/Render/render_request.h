#ifndef RENDER_REQUEST_H
#define RENDER_REQUEST_H

// Library includes
#include "resource/types.h"
#include "butter/types.h"
#include "graphics/uniformhandler.h"

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
		Matrix4 transform;
	};

	// Processed a render request (draw it to the screen)
	void ProcessRenderRequest(const TRenderRequest& _request, std::map<STRING_TYPE, TUniformHandler>& _uniforms);
}

#endif // RENDER_REQUEST_H