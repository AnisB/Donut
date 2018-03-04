// Library includes
#include "resource/common.h"

// Bento includes
#include <bento_memory/system_allocator.h>

namespace donut
{
	// Create the resource allocator
	static bento::SystemAllocator __resource_allocator;

	// This allocator should be used for everything related to resource management
	bento::IAllocator* resource_allocator()
	{
		return &__resource_allocator;
	}
}