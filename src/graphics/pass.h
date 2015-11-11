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
#ifndef PASS_GRAPHICS
#define PASS_GRAPHICS


// Library includes
#include "graphics/canvas.h"

// STL includes
#include <vector>
 
 namespace Donut
 {
	class TPass
	{
	public:
		// Constructor destructor
		TPass() {}
		virtual ~TPass() {}
		// Allocating all the CPU and GPU required memory
		virtual void Init() = 0;
		// Setting and disabling the canvas
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		// Render the VFX (using the canvas data)
		virtual void Draw(const TBufferOutput& _previousData) = 0;

		// Getting the pass output
		virtual const TBufferOutput* GetOutput() = 0;
	};
	// END CLASS DECLARATION
 }
 #endif // PASS_GRAPHICS
