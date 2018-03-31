#pragma once

// Library incldudes
#include "base/stringhelper.h"

namespace donut
{
	// Define the type
	typedef uint64_t RECIPE_GUID;

	// Generate the guid
	RECIPE_GUID GetFileHash(const STRING_TYPE& _filename);	
}