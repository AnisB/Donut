// Library includes
#include "string.h"
// External includes
#include <string.h>

namespace donut
{
	uint32_t strlen32(const char* str)
	{
		return (uint32_t)strlen(str);
	}

	TString::TString(TAllocator& allocator)
	: _allocator(allocator)
	, _data(allocator)
	{

	}

	TString::TString(const char* str, TAllocator& allocator)
	: _allocator(allocator)
	, _data(allocator)
	{
		uint32_t str_len = strlen32(str);
		if(str_len)
		{
			_data.resize(str_len + 1);
			memcpy(_data.begin(), str,  + 1);
		}
	}

	TString::TString(uint32_t str_size, TAllocator& allocator)
	: _allocator(allocator)
	, _data(allocator)
	{
		if(str_size)
		{
			_data.resize(str_size + 1);
			_data[str_size] = 0;
		}
	}
}