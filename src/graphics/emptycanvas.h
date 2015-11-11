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

#ifndef EMPTY_FRAME_CANVAS_GRAPHICS
#define EMPTY_FRAME_CANVAS_GRAPHICS

// Library includes
#include "canvas.h"

namespace Donut
{
	class TEmptyCanvas : public TCanvas
	{
	public:
		// Creation
		TEmptyCanvas(int _width, int _height);
		virtual ~TEmptyCanvas();

		// Inheritance exigences
		virtual void Init();
		virtual void Enable();
		virtual void Disable();
	};
	// END CLASS DECLARATION
}
#endif // EMPTY_FRAME_CANVAS_GRAPHICS
