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
#ifndef DONUT_DEBUG_PRINTER
#define DONUT_DEBUG_PRINTER


// STL Includes
#include <iostream>
#include <cstdio>

namespace Donut
{
	// Color list
	#define DEFAULT "\033[0m"
	#define BLACK "\033[0;30m"
	#define RED "\033[0;31m"
	#define GREEN "\033[0;32m"
	#define ORANGE "\033[0;33m"
	#define BLUE "\033[0;34m"
	#define MAGENTA "\033[0;35m"
	#define CYAN "\033[0;36m"
	#define WHITE "\033[0;37m"

	#define BOLD_TAG "\e[1m"
	#define NONBOLD_TAG "\e[0m"

	// Print terms
	#define PRINT std::cout
	#define END_PRINT DEFAULT<<std::endl

	// General print macro
	#define PRINT_GENERAL(COLOR, TYPE, ENONCE) {PRINT<<COLOR<<"["TYPE<<"] "<<ENONCE<<END_PRINT;}

	// General purpose MACROS
	#if _DEBUG
	#define PRINT_DEBUG(TYPE, ENONCE) PRINT_GENERAL(BLUE, TYPE, ENONCE)
	#elif _RELEASE
	#define PRINT_DEBUG(TYPE, ENONCE) {}
	#endif
	#define PRINT_INFO(TYPE, ENONCE) PRINT_GENERAL(GREEN, TYPE, ENONCE)
	#define PRINT_WARNING(TYPE, ENONCE) PRINT_GENERAL(ORANGE, TYPE, ENONCE)
	#define PRINT_ERROR(TYPE, ENONCE) PRINT_GENERAL(RED, TYPE, ENONCE)
}

#endif