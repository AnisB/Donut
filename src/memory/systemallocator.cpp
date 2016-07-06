// Library includes
#include "systemallocator.h"
#include "base/security.h"

namespace Donut
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
		blc.size  = 0;
		return blc;
	}

	// Frees a memory spot given
	void TSystemAllocator::deallocate(const memory_block& _blc)
	{
		free(_blc.ptr);
	}

	// Function that aswers to the question, has this bloc
	// been allocated by this allocator ?
	bool TSystemAllocator::owns(const memory_block& _blc)
	{
		return true;
	}
}