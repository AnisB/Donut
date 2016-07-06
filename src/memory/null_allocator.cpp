// Library includes
#include "null_allocator.h"
#include "base/security.h"

namespace Donut
{
	TNullAllocator::TNullAllocator()
	{
		// Nothing to do
	}

	TNullAllocator::~TNullAllocator()
	{
		// Nothing to do
	}

	// Allocate a memory chunk give a particular alignement
	memory_block TNullAllocator::allocate(size_t size, char alignment)
	{
		ASSERT_FAIL();
		memory_block blc;
		blc.ptr = nullptr;
		blc.size  = 0;
		return blc;
	}

	// Frees a memory spot given
	void TNullAllocator::deallocate(const memory_block& _blc)
	{
		ASSERT(_blc.ptr == nullptr);
	}

	// Function that aswers to the question, has this bloc
	// been allocated by this allocator ?
	bool TNullAllocator::owns(const memory_block& _blc)
	{
		return (_blc.ptr ==  nullptr);
	}
}