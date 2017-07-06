// Library includes
#include "stringhelper.h"
#include <algorithm>

// External includes
#include <vector>

namespace donut
{
	bool both_are_spaces(CHAR_TYPE lhs, CHAR_TYPE rhs) 
	{ 
		return (lhs == rhs) && (lhs == ' '); 
	}

	void removeMultSpace(STRING_TYPE& _str) 
	{
		STRING_TYPE::iterator new_end = std::unique(_str.begin(), _str.end(), both_are_spaces);
		_str.erase(new_end, _str.end());  
	}

	void split(const STRING_TYPE& parString, char parSeparator, std::vector<STRING_TYPE>& _out)
	{
		STREAM_TYPE streamObj(parString);
		STRING_TYPE item;
		while (std::getline(streamObj, item, parSeparator))
		{
			_out.push_back(item);
		}
	}
}