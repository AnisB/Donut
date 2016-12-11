// Library includes
#include "common.h"
#include <memory/systemallocator.h>

namespace Donut
{
	// Create the resource allocator
	static TAllocator* systemAllocator = make_new<TSystemAllocator>(CommonAllocator());

	// This allocator should be used for everything related to resource management
	TAllocator* ResourceAllocator()
	{
		return systemAllocator;
	}
}