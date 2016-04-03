#ifndef RECIPE_IDENTIFIER_H
#define RECIPE_IDENTIFIER_H

namespace Donut
{
	// Define the type
	typedef unsigned long int RECIPE_GUID;

	// Generate the guid
	RECIPE_GUID GenerateGUID(const char* _data);
}

#endif // RECIPE_IDENTIFIER_H