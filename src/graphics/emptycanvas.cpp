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

// Library includes
#include "emptycanvas.h"
#include "graphics/glfactory.h"

namespace donut
{
	// Creation
	TEmptyCanvas::TEmptyCanvas(int _width, int _height)
	: TCanvas(_width, _height)
	{
	}
	// Deletion
	TEmptyCanvas::~TEmptyCanvas()
	{

	}

	// Inheritance exigences
	void TEmptyCanvas::Init()
	{
	}

	void TEmptyCanvas::Enable()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void TEmptyCanvas::Disable()
	{
 		glDisable(GL_DEPTH_TEST);
	}
	// END CLASS DECLARATION
}
