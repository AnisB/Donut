// Library includes
#include "common.h"
#include <memory/system_allocator.h>

namespace donut
{
	// Create the resource allocator
	static TSystemAllocator resource_allocator;

	// This allocator should be used for everything related to resource management
	TAllocator* ResourceAllocator()
	{
		return &resource_allocator;
	}
}