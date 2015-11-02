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

#include "graphics/common.h"
#include "graphics/mesh.h"
#include "resource/sugar.h"
#include "resource/sugarloader.h"
#include "resource/resourcemanager.h"
#include "base/common.h"

namespace Donut
{
	GLfloat cubeVertexL[216] = { 
		// Vertex Data
		1.0f, -1.0f, -1.0f, // 0
		-1.0f, -1.0f, -1.0f,// 3
		1.0f, -1.0f, 1.0f,  // 1
		-1.0f, -1.0f, 1.0f, // 2
		1.0f, -1.0f, -1.0f, // 4
		1.0f, -1.0f, 1.0f,  // 5
	  	1.0f, 1.0f, -1.0f,  // 6
		1.0f, 1.0f, 1.0f,   // 7
		1.0f, -1.0f, -1.0f,  // 0
		-1.0f, -1.0f, -1.0f, // 3
	  	1.0f, 1.0f, -1.0f,   // 4
		-1.0f, 1.0f, -1.0f,   // 7
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
	  	1.0f, 1.0f, -1.0f,   // 4
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		// Normals
		0.0,-1.0,0.0,
		0.0,-1.0,0.0,
		0.0,-1.0,0.0,
		0.0,-1.0,0.0,
		1.0,0.0,0.0,
		1.0,0.0,0.0,
		1.0,0.0,0.0,
		1.0,0.0,0.0,
		0.0,0.0,-1.0,
		0.0,0.0,-1.0,
		0.0,0.0,-1.0,
		0.0,0.0,-1.0,
		0.0,1.0,0.0,
		0.0,1.0,0.0,
		0.0,1.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0,
		0.0,0.0,1.0,
		0.0,0.0,1.0,
		0.0,0.0,1.0,
		-1.0,0.0,0.0,
		-1.0,0.0,0.0,
		-1.0,0.0,0.0,
		-1.0,0.0,0.0,
		// UV Data
		0.0,0.0,
		0.0,1.0,
		1.0,0.0,
		1.0,1.0,
		0.0,0.0,
		0.0,1.0,
		1.0,0.0,
		1.0,1.0,
		0.0,0.0,
		0.0,1.0,
		1.0,0.0,
		1.0,1.0,	
		0.0,0.0,
		0.0,1.0,
		1.0,0.0,
		1.0,1.0,
		0.0,0.0,
		0.0,1.0,
		1.0,0.0,
		1.0,1.0,
		0.0,0.0,
		0.0,1.0,
		1.0,0.0,
		1.0,1.0,	
	};
	unsigned int cubeFacesL[36] = 
	{ 
		0, 1, 2,
		1, 2, 3,
		4, 5, 6,
		5, 6, 7,
		8, 9, 10,
		9, 10, 11,
		12, 13, 14,
		13, 14, 15,
		16, 17, 18,
		17, 18, 19,
		20, 21, 22,
		21, 22, 23
	};

	TMesh* CreateCube(double _length)
	{
		ASSERT_NOT_IMPLEMENTED();
		return nullptr;
	}

	TMesh* CreateSphere(double _radius)
	{
		ASSERT_NOT_IMPLEMENTED();
		return nullptr;
	}

	TMesh* CreateSugarInstance(const std::string& _sugarName)
	{
		TSugar sugar = TSugarLoader::Instance().GetSugar(_sugarName);
		ResourceManager::Instance().LoadTextures(sugar);
		ShaderManager::Instance().CreateShader(sugar.material.shader); // THIS SHOULD KEEP TRACK OF SHADER THAT USETHE SAME FILES AND RETURN A REFERENCE IF CREATED
		TGeometry* geometry = ResourceManager::Instance().GetGeometry(sugar.material.shader, sugar.geometry);
		TMesh* newMesh = new TMesh(sugar.material, geometry);
		return newMesh;
	}

}