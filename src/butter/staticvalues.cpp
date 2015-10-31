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

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

namespace Donut
{
	// Default values;
	const Vector2 v2_ZERO = vector2(0.0, 0.0);
	const Vector2 v2_X = vector2(1.0, 0.0);
	const Vector2 v2_Y = vector2(0.0, 1.0);

	// Default values;
	const Vector3 v3_ZERO = vector3(0.0, 0.0, 0.0);
	const Vector3 v3_X = vector3(1.0, 0.0, 0.0);
	const Vector3 v3_Y = vector3(0.0, 1.0, 0.0);
	const Vector3 v3_Z = vector3(0.0, 0.0, 1.0);

	// Default values;
	const Vector4 v4_ZERO = vector4(0.0, 0.0, 0.0, 0.0);
	const Vector4 v4_X = vector4(1.0, 0.0, 0.0, 0.0);
	const Vector4 v4_Y = vector4(0.0, 1.0, 0.0, 0.0);
	const Vector4 v4_Z = vector4(0.0, 0.0, 1.0, 0.0);
	const Vector4 v4_W = vector4(0.0, 0.0, 0.0, 1.0);
}