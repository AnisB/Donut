// Library includes
#include "stringhelper.h"
#include <algorithm>

// External includes
#include <vector>

namespace Donut
{

	bool BothAreSpaces(CHAR_TYPE lhs, CHAR_TYPE rhs) 
	{ 
		return (lhs == rhs) && (lhs == ' '); 
	}

	void removeMultSpace(STRING_TYPE& _str) 
	{
		STRING_TYPE::iterator new_end = std::unique(_str.begin(), _str.end(), BothAreSpaces);
		_str.erase(new_end, _str.end());  
	}

	void split(const std::string& parString, char parSeparator, std::vector<std::string>& _out)
	{
		std::stringstream streamObj(parString);
		std::string item;
		while (std::getline(streamObj, item, parSeparator))
		{
			_out.push_back(item);
		}
	}
}