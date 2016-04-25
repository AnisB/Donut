#ifndef RECIPE_IDENTIFIER_H
#define RECIPE_IDENTIFIER_H

#include "base/common.h"

namespace Donut
{
	// Define the type
	typedef unsigned long int RECIPE_GUID;

	// Generate the guid
	RECIPE_GUID GetFileHash(const std::string& _filename);	
}

#endif // RECIPE_IDENTIFIER_H