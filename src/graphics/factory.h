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
#include "graphics/mesh.h"

namespace Donut
{
	TMesh* CreateCube(double _length, const TShader& _shader);
	TMesh* CreateSphere(double _radius);
	TMesh* CreatePlane(double _with, double _length, const TShader& _shader);
	TMesh* CreateSugarInstance(const std::string& _sugarName);
}
