#pragma once

// Library includes
#include "memory/common.h"
#include "base/platform.h"
#include "base/security.h"

namespace donut
{
	template <typename T>
	class TArray
	{
	public:
		ALLOCATOR_BASED;

		// Type definition
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef pointer iterator;
		typedef const_pointer const_iterator;


		// Default constructor
		TArray(TAllocator& allocator);

		// Size aware constructor
		TArray(uint32_t size, TAllocator& allocator);

		// Dst
		~TArray();

		// Accessors
		inline uint32_t size() {return _size;}
		inline uint32_t capacity() {return _capacity;}

		// Resize the array
		void resize(uint32_t size);

		// Free the memory
		void free();

		// Set the size to 0
		void clear();

		// Reserve memory in the array
		void reserve(uint32_t _space);

		inline T& operator[](uint32_t index)
		{
			ASSERT_NO_RELEASE(index < _size);
			return _data[index];
		}

		// Append an element in the array
		void push_back(const T& _value);

		// Iterator access
		inline iterator begin() {return _data;}
		inline const_iterator begin() const {return _data;}
		inline iterator end() {return _data + _size;}
		inline const_iterator end() const {return _data + _size;}

	protected:
		T* _data;
		uint32_t _size;
		uint32_t _capacity;

		// Allocator for this class
		TAllocator& _allocator;
	};
}

#include "array.inl"