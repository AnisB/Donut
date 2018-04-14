// Bento includes
#include <bento_memory/system_allocator.h>

namespace donut
{
	static bento::SystemAllocator allocator;

	bento::IAllocator* graphics_allocator()
	{
		return &allocator;
	}
}