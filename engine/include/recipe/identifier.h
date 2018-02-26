#ifndef RECIPE_IDENTIFIER_H
#define RECIPE_IDENTIFIER_H

// Library incldudes
#include "base/platform.h"
#include "base/stringhelper.h"

namespace donut
{
	// Define the type
	typedef uint64_t RECIPE_GUID;

	// Generate the guid
	RECIPE_GUID GetFileHash(const STRING_TYPE& _filename);	
}

#endif // RECIPE_IDENTIFIER_H