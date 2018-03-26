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

#pragma once

// donut includes
#include <base/log.h>
#include <bento_memory/common.h>

namespace donut
{
	#define __RESOURCE_PRINT_NAMESPACE "RESOURCE"
	
	// Printing macros
	#define RESOURCE_DEBUG(ENONCE) PRINT_DEBUG (__RESOURCE_PRINT_NAMESPACE, ENONCE)
	#define RESOURCE_WARNING(ENONCE) PRINT_WARNING (__RESOURCE_PRINT_NAMESPACE, ENONCE)
	#define RESOURCE_INFO(ENONCE) PRINT_INFO (__RESOURCE_PRINT_NAMESPACE, ENONCE)
	#define RESOURCE_ERROR(ENONCE) PRINT_ERROR (__RESOURCE_PRINT_NAMESPACE, ENONCE)	

	// This allocator should be used for everything related to resource management
	bento::IAllocator* resource_allocator();
}
