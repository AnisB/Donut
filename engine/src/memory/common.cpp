// Library includes
#include "memory/common.h"
#include "memory/system_allocator.h"

namespace donut
{
	// This variable is used to process all common memory space allocation (if no particular behavior)
	// is requested, this is only new that is tolered in the whole library.
	static TSystemAllocator __common_allocator;

	// Return the common allocator ptr
	TAllocator* common_allocator()
	{
		return &__common_allocator;
	}
}