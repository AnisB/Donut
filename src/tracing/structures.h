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

#include <butter/Vector3.h>
#include <butter/Vector2.h>

namespace Donut
{
	struct TVertice
	{
		Vector3 position;
		Vector3 normal;
		Vector2 uv;
	};

	struct TRay
	{
		Vector3 origin;
		Vector3 direction;
	};


	struct TIntersect
	{
		TIntersect()
		{
			isValid = false;
		}	

		bool isValid;
		float distance;
		TVertice point;
	};
}