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
 
 #include "InputManager.h"

 #include <Base/DebugPrinters.h>

 namespace Donut
 {
	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}
	void InputManager::KeyPressed(TKeyCode::Type parKey)
	{
		INPUT_DEBUG("Key pressed: "<<parKey);
	}
	void InputManager::KeyReleased(TKeyCode::Type parKey)
	{
		INPUT_DEBUG("Key released: "<<parKey);
	}

	void InputManager::MouseMoved(float parX, float parY)
	{
		INPUT_DEBUG("Mouse moved: "<<parX<< " "<<parY);
	}
	void InputManager::MousePressed(TMouseCode::Type parButton)
	{
		INPUT_DEBUG("Button pressed: "<<parButton);
	}
	void InputManager::MouseReleased(TMouseCode::Type parButton)
	{
		INPUT_DEBUG("Button released: "<<parButton);
	}
 }

