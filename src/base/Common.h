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
#ifndef DONUT_BASE_COMMON
#define DONUT_BASE_COMMON

// Donut Includes
#include "const.h"
#include "exception.h"
#include "macro.h"
#include "stringhelper.h"
#include "security.h"
#include "singleton.h"
#include "printers.h"

namespace Donut
{
	#define __GENERAL_PRINT_NAMESPACE "GENERAL"
	
	// Printing macros
	#define GENERAL_DEBUG(ENONCE) PRINT_DEBUG (__GENERAL_PRINT_NAMESPACE, ENONCE)
	#define GENERAL_WARNING(ENONCE) PRINT_WARNING (__GENERAL_PRINT_NAMESPACE, ENONCE)
	#define GENERAL_INFO(ENONCE) PRINT_INFO (__GENERAL_PRINT_NAMESPACE, ENONCE)
	#define GENERAL_ERROR(ENONCE) PRINT_ERROR (__GENERAL_PRINT_NAMESPACE, ENONCE)
}
#endif // DONUT_BASE_COMMON
