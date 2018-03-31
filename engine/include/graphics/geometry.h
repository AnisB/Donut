#pragma once

#include "core/box3.h"

namespace donut
{
	struct TGeometry
	{
		// Runtime rendering data
		uint32_t vertexArray;
		uint32_t vertexBuffer;
		uint32_t indexBuffer;
	    int nbVertices;

		// Useful data
		TBox3 os_bb;

		// Draw the geometry
	    void Draw(bool _isTess) const;
	};	
}