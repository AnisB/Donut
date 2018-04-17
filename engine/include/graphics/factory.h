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
#include "core/mesh.h"

namespace donut
{
	// Foward declaration
	class TSugarInstance;

	GEOMETRY_GUID CreateFullScreenQuad(const TShader& _shader);

	// Drawable factory
	TMesh* CreateSkyboxDrawable(TSkyboxTexture* skybox_tex);
	
		// Default meshes
	TMesh* CreateCube(double _length, STRING_TYPE _materialName = "DEFAULT");
	TMesh* CreateSphere(double _radius, STRING_TYPE _materialName = "DEFAULT");
	TMesh* CreatePlane(double _with, double _length, STRING_TYPE _materialName = "DEFAULT");
		// Create a sugar instance
	TSugarInstance* CreateSugarInstance(const STRING_TYPE& _sugarName);
}
