// Library include
#include "identifier.h"

// External include
#include <string>

namespace Donut
{
	RECIPE_GUID GenerateGUID(const char* _data)
	{
		return std::hash<const char*>()(_data);
	}
}