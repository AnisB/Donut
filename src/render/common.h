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

#ifndef RENDER_COMMON_H
#define RENDER_COMMON_H

#include <GL/glew.h>

#ifndef GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GL3
#endif
 
#include <GLFW/glfw3.h>

// Donut includes
#include <base/printers.h>

namespace Donut
{
	#define FLUSH_GL_ERROR "__FLUSH_ME_PLEASE"

	#define __RENDER_PRINT_NAMESPACE "RENDER"
	
	// Printing macros
	#define RENDER_DEBUG(ENONCE) PRINT_DEBUG (__RENDER_PRINT_NAMESPACE, ENONCE)
	#define RENDER_WARNING(ENONCE) PRINT_WARNING (__RENDER_PRINT_NAMESPACE, ENONCE)
	#define RENDER_INFO(ENONCE) PRINT_INFO (__RENDER_PRINT_NAMESPACE, ENONCE)
	#define RENDER_ERROR(ENONCE) PRINT_ERROR (__RENDER_PRINT_NAMESPACE, ENONCE)	
}

#endif // RENDER_COMMON_H