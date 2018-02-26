#ifndef BASE_STRING_HELPER_H
#define BASE_STRING_HELPER_H

// External includes
#include <string.h>
#include <sstream>
#include <vector>

namespace donut
{
	// The string base and types (in case i'd like to move to wstring or whatever)
	#define STRING_TYPE std::string
	#define CHAR_TYPE char
	#define STREAM_TYPE std::stringstream

	// Generic converter to string
	template <typename T>
	STRING_TYPE convert_to_string(const T& _value)
	{
		STREAM_TYPE stream;
		stream << _value;
		return stream.str();
	}

	// Generic converter from string
	template <typename T>
	T convert_from_string(const STRING_TYPE& _string)
	{
		STREAM_TYPE stream(_string);
		T val;
		stream >> val;
		return val;
	}

	// Takes a string and removes multiple spaces from it
	void remove_multiple_spaces(STRING_TYPE& parString);

	// Splits parstring with parSeparator
	void split(const STRING_TYPE& parString, char parSeparator, std::vector<STRING_TYPE>& _out);
}

#endif // BASE_STRING_HELPER_H