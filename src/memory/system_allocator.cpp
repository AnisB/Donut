// Library includes
#include "system_allocator.h"
#include "base/security.h"

namespace donut
{
	TSystemAllocator::TSystemAllocator()
	{
		// Nothing to do
	}

	TSystemAllocator::~TSystemAllocator()
	{
		// Nothing to do
	}

	// Allocate a memory chunk give a particular alignement
	memory_block TSystemAllocator::allocate(size_t size, char alignment)
	{
		memory_block blc;
		blc.ptr = malloc(size);
		blc.size  = size;
		return blc;
	}

	// Frees a memory spot given
	void TSystemAllocator::deallocate(void* _ptr)
	{
		free(_ptr);
	}
}