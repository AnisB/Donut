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

//Includes engine
#include <Render/Renderer.h>
#include <base/common.h>
#include <Input/InputHelper.h>
#include <Input/DefaultInputManager.h>
#include <resource/sugarloader.h>
#include <resource/texturehelpers.h>
#include <Render/Representations/3D/Mesh.h>
#include <core/sceneNode.h>
#include <resource/texture.h>
#include <resource/resourcemanager.h>

// Autres includes
#include <cmath> 

using namespace Donut;

int main()
{
	Donut::TSugarLoader::Instance().Init("data");
	std::vector<TTexture*> triangles;
	Donut::ResourceManager::Instance().LoadObjToTexture("data/models/lego/legodude.obj",triangles);
	TextureHelpers::CreateDataTexture(triangles[0]);
	return 0;
}
