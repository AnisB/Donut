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

// Donut includes
#include "security.h"
#include "exception.h"
#include "const.h"
#include <base/common.h>

// STL include
#include <unistd.h>
#include <execinfo.h>

namespace Donut
{
	void printTrace()
	{
	    void *array[EXCEPTION_STACK_SIZE];
	    size_t size;
	    size = backtrace(array, EXCEPTION_STACK_SIZE);
	    backtrace_symbols_fd(array, size, STDERR_FILENO);	
	}

	void __handleFail(std::string _message)
	{
		GENERAL_ERROR(_message);
		printTrace();
		throw TException(_message);
	}

	
}
