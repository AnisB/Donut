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
		ASSERT_FAIL_MSG("Null allocator cannot allocate memory");
		memory_block blc;
		blc.ptr = nullptr;
		blc.size  = 0;
		return blc;
	}

	// Frees a memory spot given
	void TNullAllocator::deallocate(void* _ptr)
	{
		ASSERT_MSG(_ptr == nullptr, "The null allocator cannot free non-nullptrs.");
	}

	// Function that aswers to the question, has this bloc
	// been allocated by this allocator ?
	bool TNullAllocator::owns(void* _ptr)
	{
		return (_ptr ==  nullptr);
	}
}