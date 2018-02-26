#pragma once

// Library includes
#include "allocator.h"

namespace donut
{
	// SFNIAE based member for allocation based class
	#define ALLOCATOR_BASED int allocator_based;

	// Convert integer to type.
	template <int v>
	struct Int2Type { enum {value=v}; };

	// Determines if a class is based on the allocation system
	template <class T>
	struct is_allocator_based {

		template <typename C>
		static char dummy_func(typename C::allocator_based *);

		template <typename C>
		static int dummy_func(...);

	public:
		enum {
			value = (sizeof(dummy_func<T>(0)) == sizeof(char))
		};
	};

	// Helper macros for allocation detection
	#define IS_ALLOCATOR_BASED(T) is_allocator_based<T>::value
	#define IS_ALLOCATOR_BASED_TYPE(T) Int2Type< IS_ALLOCATOR_BASED(T) >

	// Allocator based constuction
	template <class T> inline T &construct(void *p, TAllocator &a, Int2Type<true>) {new (p) T(a); return *(T *)p;}
	template <class T> inline T &construct(void *p, TAllocator &a, Int2Type<false>) {new (p) T; return *(T *)p;}
	template <class T> inline T &construct(void *p, TAllocator &a) {return construct<T>(p, a, IS_ALLOCATOR_BASED_TYPE(T)());}

	// This function sets should be used instead of the classic new operator
	// new operator should be forbitten. 

	// This one concernes all the object that need to be created using a default constructor
	template<typename T>
	T* make_new(TAllocator* _allocator)
	{
		// Allocate the memory space that matches the target type
		memory_block allocated = _allocator->allocate(sizeof(T));
		// Build, cast and return the allocated memory in the right type
		return new (allocated.ptr) T();
	}

	// This one concernes all the object that need to be created using a one parameter constructor
	template<typename T, typename P1>
	T* make_new(TAllocator* _allocator, P1& _p1)
	{
		// Allocate the memory space that matches the target type
		memory_block allocated = _allocator->allocate(sizeof(T));
		// Build, cast and return the allocated memory in the right type
		return new (allocated.ptr) T(_p1);
	}	

	// This one concernes all the object that need to be created using a two parameter constructor
	template<typename T, typename P1, typename P2>
	T* make_new(TAllocator* _allocator, P1& _p1, P2& _p2)
	{
		// Allocate the memory space that matches the target type
		memory_block allocated = _allocator->allocate(sizeof(T));
		// Build, cast and return the allocated memory in the right type
		return new (allocated.ptr) T(_p1, _p2);
	}	

	// This function is the way to delete objects that have been allocated 
	// using a donut::TAllocator.
	template<typename T>
	void make_delete(TAllocator& allocator, T* _targetPtr)
	{
		// Deallocates the memory
		allocator.deallocate(_targetPtr);
	}

	// This function should be called to fetch the default common allocator, if a specific 
	// allocation behavior is not required aat the spot you call it.
	TAllocator* common_allocator();
}
