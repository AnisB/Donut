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
		_data.resize(str_len);
		memcpy(_data.begin(), str, str_len);
	}
}