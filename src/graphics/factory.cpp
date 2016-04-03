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
#include "factory.h"
#include "base/common.h"
#include "graphics/common.h"
#include "graphics/mesh.h"
#include "resource/sugarloader.h"
#include "resource/resourcemanager.h"

namespace Donut
{
	// Cube Data
	GLfloat cubeVertexL[216] = { 
		// Vertex Data
	1.0f, -1.0f, -1.0f, // 0
	-1.0f, -1.0f, -1.0f,// 3
	1.0f, -1.0f, 1.0f,  // 1
	-1.0f, -1.0f, 1.0f, // 2

	// 4 5 6 // 4 6 7 
	1.0f, -1.0f, -1.0f, 
	1.0f, -1.0f, 1.0f,  // 1
  	1.0f, 1.0f, -1.0f,   // 4
	1.0f, 1.0f, 1.0f,    // 5


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


	// Plane Data
	GLfloat planeVertexBuffer[32] = { 
		// Vertex Data
	1.0f, 0.0f, -1.0f, // 0
	-1.0f, 0.0f, -1.0f,// 3
	1.0f, 0.0f, 1.0f,  // 1
	-1.0f, 0.0f, 1.0f, // 2

	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0,

	0.0,0.0,
	0.0,1.0,
	1.0,0.0,
	1.0,1.0,	
	};
	unsigned int planeIndexBuffer[6] = 
	{ 
		0, 1, 2,
		2, 1, 3
	};
	// Full screen Quad Data
	GLfloat FSQVertex[32] = { 
		-1.0f, -1.0f, 0.0f, 
		-1.0f, 1.0f, 0.0f, 
		1.0f, -1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f,
		0.0, 0.0, 1.0, 
		0.0, 0.0, 1.0, 
		0.0, 0.0, 1.0, 
		0.0, 0.0, 1.0, 
		0.0,0.0,
		0.0,1.0,
		1.0,0.0,
		1.0,1.0,
	};
	unsigned int FSQIndex[32] = { 
		0, 1, 2,
		1, 2, 3
	};

	TMesh* CreateCube(double _length, const TShader& _shader)
	{
		static int cubeCounter = 0;
 		GLfloat data[216];
 		memcpy(&data ,&cubeVertexL, 216*sizeof(float));
 		for(int i = 0; i<72; ++i)
 		{
 			data[i]*=(GLfloat)_length;
 		}
 		std::string meshName = "Cube_";
 		TMaterial defaultMat;
 		defaultMat.shader = _shader;
 		meshName += std::to_string(cubeCounter++);
 		GRAPHICS_DEBUG("Creating cube "<<meshName);
		ShaderManager::Instance().CreateShader(defaultMat.shader);
		TGeometry* geometry = ResourceManager::Instance().CreateGeometry(meshName, defaultMat.shader, data, 24, cubeFacesL, 12);
		TMesh* newMesh = new TMesh(defaultMat, geometry);
		return newMesh;
	}

	TMesh* CreatePlane(double _with, double _length, const TShader& _shader)
	{
		static int planeCounter = 0;
 		GLfloat data[32];
 		memcpy(&data ,&planeVertexBuffer, 32*sizeof(float));
 		for(int i = 0; i<4; ++i)
 		{
 			data[3*i]*=(GLfloat)_with;
 		}
 		for(int i = 0; i<4; ++i)
 		{
 			data[3*i+2]*=(GLfloat)_length;
 		}
 		std::string meshName = "Plane_";
 		TMaterial defaultMat;
 		defaultMat.shader = _shader;
 		meshName += std::to_string(planeCounter++);
 		GRAPHICS_DEBUG("Creating plane "<<meshName);
		ShaderManager::Instance().CreateShader(defaultMat.shader); 
		TGeometry* geometry = ResourceManager::Instance().CreateGeometry(meshName, defaultMat.shader, data, 4, planeIndexBuffer, 2);
		TMesh* newMesh = new TMesh(defaultMat, geometry);
		return newMesh;
	}

	TMesh* CreateSphere(double _radius)
	{
		ASSERT_NOT_IMPLEMENTED();
		return nullptr;
	}

	TMesh* CreateSugarInstance(const std::string& _sugarName)
	{
		TSugarDescriptor sugar = TSugarLoader::Instance().FetchSugar(_sugarName);
		foreach_macro(tex, sugar.material.textures)
		{
			TTexture* texPtr = ResourceManager::Instance().FetchTexture(tex->file);
  			tex->texID = texPtr->FID;
		}
		ShaderManager::Instance().CreateShader(sugar.material.shader); 
		TGeometry* geometry = ResourceManager::Instance().FetchGeometry(sugar.material.shader, sugar.geometry);
		TMesh* newMesh = new TMesh(sugar.material, geometry);
		return newMesh;
	}

	TGeometry* CreateFullScreenQuad(const TShader& _shader)
	{
		static int FSQCounter = 0;
		TMaterial defaultMat;
 		defaultMat.shader = _shader;
 		std::string meshName = "FSQ_";
 		meshName += std::to_string(FSQCounter++);
 		GRAPHICS_DEBUG("Creating FSQ "<<meshName);
		ShaderManager::Instance().CreateShader(defaultMat.shader); 
		TGeometry* geometry = ResourceManager::Instance().CreateGeometry(meshName, defaultMat.shader, FSQVertex, 4, FSQIndex, 2);
		return geometry;
	}

	TMesh* CreateSkybox(const std::string& _folderName, const std::string& _extension)
	{	
		// Fetch the texture
		TSkyboxTexture* skybox = ResourceManager::Instance().FetchSkybox(_folderName, _extension);
		// Create the shader
		TShader shader("common/shaders/skybox/vertex.glsl", "common/shaders/skybox/fragment.glsl");
		ShaderManager::Instance().CreateShader(shader); 
		// Create the material
		TMaterial skyboxMat;
 		skyboxMat.shader = shader;
 		TCubeMapInfo newCM;
		newCM.cmID = skybox->id;
		newCM.offset = 0;
		newCM.name = "skybox";
		skyboxMat.cubeMaps.push_back(newCM);
		// Create the geometry
		TGeometry* fsq = CreateFullScreenQuad(shader);
		return new TMesh(skyboxMat, fsq);
	}

}