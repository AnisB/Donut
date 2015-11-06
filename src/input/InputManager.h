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

#ifndef INPUT_MANAGER_DONUT 
#define INPUT_MANAGER_DONUT

#include "defines.h"
#include <base/common.h>

namespace Donut
{
	class TInputManager
	{
	public:
		TInputManager();
		virtual ~TInputManager();

		virtual void KeyPressed(TKeyCode::Type parKey) = 0;
		virtual void KeyReleased(TKeyCode::Type parKey) = 0;

		virtual void MouseMoved(double parX, double parY) = 0;
		virtual void MousePressed(TMouseCode::Type parButton) = 0;
		virtual void MouseReleased(TMouseCode::Type parButton) = 0;
	};
}

 #endif //INPUT_MANAGER_DONUT