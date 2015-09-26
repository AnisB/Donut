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

#ifndef ENGINE_COMMON_H
#define ENGINE_COMMON_H


// Donut includes
#include <base/printers.h>

namespace Donut
{
	#define __ENGINE_PRINT_NAMESPACE "ENGINE"
	
	// Printing macros
	#define ENGINE_DEBUG(ENONCE) PRINT_DEBUG (__ENGINE_PRINT_NAMESPACE, ENONCE)
	#define ENGINE_WARNING(ENONCE) PRINT_WARNING (__ENGINE_PRINT_NAMESPACE, ENONCE)
	#define ENGINE_INFO(ENONCE) PRINT_INFO (__ENGINE_PRINT_NAMESPACE, ENONCE)
	#define ENGINE_ERROR(ENONCE) PRINT_ERROR (__ENGINE_PRINT_NAMESPACE, ENONCE)	
}

#endif // ENGINE_COMMON_H