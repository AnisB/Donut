// Library includes
#include "common.h"
#include "memory/systemallocator.h"

namespace Donut
{
	static TSystemAllocator allocator;

	TAllocator* graphics_allocator()
	{
		return &allocator;
	}
}