#pragma once

// Library includes
#include "array.h"
#include "base/platform.h"

namespace donut
{
	// Computes the length of a string
	uint32_t strlen32(const char* str);

	class TString
	{
	public:
		ALLOCATOR_BASED;

		// Cst
		TString(TAllocator& allocator);
		TString(const char* str, TAllocator& allocator);

		// Accessors
		inline char* str() { return _data.begin(); }
		inline const char* c_str() const { return _data.begin(); }

	private:
		// raw memory for the string
		TArray<char> _data;
		// Allocator member for this class
		TAllocator& _allocator;
	};
}