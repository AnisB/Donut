#ifndef FALLBACK_ALLOCATOR_H
#define FALLBACK_ALLOCATOR_H

// Library includes
#include "allocator.h"

namespace Donut
{
	template<typename TFirstAllocator, typename TSecondAllocator>
	class TFallBackAllocator : public TAllocator
	{
	public:
		TFallBackAllocator();
		~TFallBackAllocator();

		// Allocate a memory chunk give a particular alignement
		virtual memory_block allocate(size_t size, char alignment = 4);

		// Frees a memory spot given
		virtual void deallocate(void* _ptr);

		// Function that aswers to the question, has this bloc
		// been allocated by this allocator ?
		virtual bool owns(void* _ptr);

	protected:
		TFirstAllocator m_first;
		TSecondAllocator m_second;
	};
}

// Implementation header include
#include "combine_allocator.h"

#endif // FALLBACK_ALLOCATOR_H