/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/

#ifndef DONUT_EXCEPTIONS_H
#define DONUT_EXCEPTIONS_H

// Library include
#include "stringhelper.h"

// STL Includes
#include <exception>
#include <string>

namespace Donut
{
	struct TException : public std::exception
	{
		TException(const STRING_TYPE& _message, const CHAR_TYPE* _file, int _line)
		: message(_message)
		, file(_file)
		, line(_line)
		{

		}

		virtual ~TException() throw() {}
		STRING_TYPE message;
		STRING_TYPE file;
		int line;
	};
}

#endif // DONUT_EXCEPTIONS_H