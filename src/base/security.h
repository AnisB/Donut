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
#ifndef DONUT_BASE_SECURITY
#define DONUT_BASE_SECURITY

// Library includes
#include "stringhelper.h"

// STL Includes
#include <iostream>
#include <sstream>

namespace donut
{
	// Final function
	void __handleFail(STRING_TYPE _message, const CHAR_TYPE* _file, int _line);

	// Fail function with messages
	#define ASSERT_FAIL_MSG(MSG) {STREAM_TYPE stream; stream<<MSG;  donut::__handleFail(stream.str(), __FILE__, __LINE__);}
	#define ASSERT_FAIL() {ASSERT_FAIL_MSG("");}
	#define ASSERT(Enonce) {if(!(Enonce)) ASSERT_FAIL_MSG ("");}
	#define ASSERT_MSG(Enonce, MSG) {if(!(Enonce)) ASSERT_FAIL_MSG(MSG);}
	#define ASSERT_NOT_IMPLEMENTED() {ASSERT_FAIL_MSG("Currently not implemented");}

#ifdef _DEBUG
	#define ASSERT_POINTER_NOT_NULL_NO_RELEASE(ptr) {ASSERT_MSG(ptr != nullptr, "Pointer was null");} 
	#define ASSERT_FAIL_NO_RELEASE() ASSERT_FAIL()
	#define ASSERT_FAIL_MSG_NO_RELEASE(MSG) ASSERT_FAIL_MSG(MSG)
	#define ASSERT_NO_RELEASE(Enonce) ASSERT(Enonce)
	#define ASSERT_MSG_NO_RELEASE(Enonce, MSG) ASSERT_MSG(Enonce, MSG)
#else
	#define ASSERT_POINTER_NOT_NULL_NO_RELEASE(ptr) {}
	#define ASSERT_FAIL_NO_RELEASE() {}
	#define ASSERT_FAIL_MSG_NO_RELEASE(MSG) {}
	#define ASSERT_NO_RELEASE(Enonce) {}
	#define ASSERT_MSG_NO_RELEASE(Enonce, MSG) {}
#endif
	
}

#endif // DONUT_BASE_SECURITY
