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


#ifndef DONUT_DRAWABLE_OBJECT
#define DONUT_DRAWABLE_OBJECT

// Library includes
#include "graphics/uniformhandler.h"
#include "graphics/canvas.h"
#include "render/collector.h"

namespace donut
{
	class TDrawable
	{
	public:
		// Cst & Dst
		TDrawable();
		virtual ~TDrawable();

		// Evaluate the drawable
		virtual void Evaluate(TCollector& _collector, const bento::Matrix4& _tm) = 0;
	};
}
 #endif // DONUT_DRAWABLE_OBJECT