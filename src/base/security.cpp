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
#include "common.h"

// STL include
#if __posix__
#include <unistd.h>
#include <execinfo.h>
#endif

namespace Donut
{
	void printTrace()
	{
		#if __posix__
	    void *array[EXCEPTION_STACK_SIZE];
	    size_t size;
	    size = backtrace(array, EXCEPTION_STACK_SIZE);
	    backtrace_symbols_fd(array, size, STDERR_FILENO);
		#endif
	}

	void __handleFail(std::string _message)
	{
		GENERAL_ERROR(_message);
		#if __posix__
		printTrace();
		#endif
		throw TException(_message);
	}

	
}
