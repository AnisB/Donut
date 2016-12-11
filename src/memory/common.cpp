// Library includes
#include "common.h"
#include "systemallocator.h"

namespace Donut
{
	// This variable is used to process all common memory space allocation (if no particular behavior)
	// is requested, this is only new that is tolered in the whole library.
	static TAllocator* commonAllocator = new TSystemAllocator();

	// Return the common allocator ptr
	TAllocator* CommonAllocator()
	{
		return commonAllocator;
	}
}