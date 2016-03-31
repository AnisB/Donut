// Library includes
#include "stringhelper.h"
#include <algorithm>

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
}