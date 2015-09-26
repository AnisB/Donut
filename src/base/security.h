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

// STL Includes
#include <iostream>
#include <sstream>

namespace Donut
{
	void __handleFail(std::string _message);
	#define ASSERT(Enonce) {if(!(Enonce)) __handleFail("");}
	#define ASSERT_MSG(Enonce, MSG) {if(!(Enonce)){std::stringstream stream; stream<<MSG;  __handleFail(stream.str()); };}
#ifdef _DEBUG
	#define ASSERT_NO_RELEASE(Enonce) {if(!(Enonce)) __handleFail("");}
	#define ASSERT_MSG_NO_RELEASE(Enonce, MSG) {if(!(Enonce)){std::stringstream stream; stream<<MSG;  __handleFail(stream.str()); };}
#elif _RELEASE 
	#define ASSERT_NO_RELEASE(Enonce) {}
	#define ASSERT_MSG_NO_RELEASE(Enonce) {}
#endif
}

#endif // DONUT_BASE_SECURITY
