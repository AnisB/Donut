#ifndef NULL_ALLOCATOR_H
#define NULL_ALLOCATOR_H

// Library includes
#include "allocator.h"

namespace Donut
{
	class TNullAllocator : public TAllocator
	{
	public:
		TNullAllocator();
		~TNullAllocator();

		// Allocate a memory chunk give a particular alignement
		virtual memory_block allocate(size_t size, char alignment = 4);

		// Frees a memory spot given
		virtual void deallocate(void* _ptr);

		// Function that aswers to the question, has this bloc
		// been allocated by this allocator ?
		virtual bool owns(void* _ptr);
	};
}

#endif // NULL_ALLOCATOR_H