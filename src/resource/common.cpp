// Library includes
#include "common.h"
#include <memory/system_allocator.h>

namespace donut
{
	// Create the resource allocator
	static TSystemAllocator __resource_allocator;

	// This allocator should be used for everything related to resource management
	TAllocator* resource_allocator()
	{
		return &__resource_allocator;
	}
}