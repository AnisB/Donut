#pragma once

// External includes
#include <stdint.h>

namespace donut
{
	enum class ResourceType
	{
		texture = 0,
		shader = 1,
		sugar = 2,
		topping = 3,
		pipeline = 4,
		flour = 5,
		egg = 6,
		none = 7
	};

	typedef uint32_t GEOMETRY_GUID;
	typedef uint32_t TEXTURE_GUID;
	typedef uint32_t CUBEMAP_GUID;
	typedef uint32_t MATERIAL_GUID;
}