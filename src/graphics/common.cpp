// Library includes
#include "common.h"
#include "memory/system_allocator.h"

namespace donut
{
	static TSystemAllocator allocator;

	TAllocator* graphics_allocator()
	{
		return &allocator;
	}
}