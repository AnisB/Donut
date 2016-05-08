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

#ifndef CORE_COMMON_H
#define CORE_COMMON_H


// Donut includes
#include <base/log.h>

namespace Donut
{
	#define __CORE_PRINT_NAMESPACE "CORE"
	
	// Printing macros
	#define CORE_DEBUG(ENONCE) PRINT_DEBUG (__CORE_PRINT_NAMESPACE, ENONCE)
	#define CORE_WARNING(ENONCE) PRINT_WARNING (__CORE_PRINT_NAMESPACE, ENONCE)
	#define CORE_INFO(ENONCE) PRINT_INFO (__CORE_PRINT_NAMESPACE, ENONCE)
	#define CORE_ERROR(ENONCE) PRINT_ERROR (__CORE_PRINT_NAMESPACE, ENONCE)	
}

#endif // CORE_COMMON_H