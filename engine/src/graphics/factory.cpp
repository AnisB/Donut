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
#include "graphics/factory.h"
#include "core/sugarinstance.h"
#include "core/mesh.h"
#include "graphics/common.h"
#include "core/mesh.h"
#include "resource/sugar_loader.h"
#include "resource/resourcemanager.h"
#include "resource/toppingloader.h"

// External includes
#include <float.h>

namespace donut
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

	TMesh* CreateCube(double _length, STRING_TYPE _materialName)
	{
		static int cubeCounter = 0;
 		GLfloat data[216];
 		memcpy(&data ,&cubeVertexL, 216*sizeof(float));
 		for(int i = 0; i<72; ++i)
 		{
 			data[i]*=(GLfloat)_length;
 		}

		TOPPING_GUID topping = TToppingLoader::Instance().FetchMaterial(_materialName);
		const TMaterial* mat = TToppingLoader::Instance().RequestRuntimeMaterial(topping);

		// Generating the geometry name
 		STRING_TYPE meshName = "Cube_";
 		meshName += std::to_string(cubeCounter++);
 		
 		// Creating the geometry
 		GRAPHICS_DEBUG("Creating cube "<<meshName);
		GEOMETRY_GUID geometry = ResourceManager::Instance().InstanciateRunTimeGeometry(meshName, mat->shader, data, 24, cubeFacesL, 12);
		
		// Create the mesh instance
		TMesh* newMesh = new TMesh(topping, geometry);

		// return it
		return newMesh;
	}

    TMesh* CreatePlane(double _with, double _length, STRING_TYPE _materialName)
	{
		// Create the geometry buffer
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

 		// Generate the geometry name
 		STRING_TYPE meshName = "Plane_";
 		meshName += std::to_string(planeCounter++);

		TOPPING_GUID topping = TToppingLoader::Instance().FetchMaterial(_materialName);
		const TMaterial* mat = TToppingLoader::Instance().RequestRuntimeMaterial(topping);

		// Create the target geometry
 		GRAPHICS_DEBUG("Creating plane "<<meshName);
		GEOMETRY_GUID geometry = ResourceManager::Instance().InstanciateRunTimeGeometry(meshName, mat->shader, data, 4, planeIndexBuffer, 2);

		// Create the mesh instance
		TMesh* newMesh = new TMesh(topping, geometry);

		// return it
		return newMesh;
	}

	TMesh* CreateSphere(double _radius)
	{
		assert_fail();
		return nullptr;
	}

	TSugarInstance* CreateSugarInstance(const STRING_TYPE& _sugarName)
	{
		// Fetch the sugar descriptor
		const TSugarDescriptor& sugar = TSugarLoader::Instance().FetchSugar(_sugarName);

		// Create a sugar instance
		TSugarInstance* newSugarInstance = new TSugarInstance();

		// For each renderable in the renderables array
		for(auto& renderable : sugar._renderables)
		{
			// Fetch the renderable descriptor
			const TRenderableDescriptor& renderableDescriptor = renderable;

			// Fetch the material
			TOPPING_GUID topping = TToppingLoader::Instance().FetchMaterial(renderableDescriptor._material);
			const TMaterial* mat = TToppingLoader::Instance().RequestRuntimeMaterial(topping);
			
			// Fetch the geometry
			GEOMETRY_GUID geometry = ResourceManager::Instance().FetchGeometry(mat->shader, renderableDescriptor._geometry);
			
			// Create the renderable mesh
			TMesh* newMesh = new TMesh(topping, geometry);

			// Add the mesh to the sugar instance
			newSugarInstance->AddMesh(newMesh);
		}

		// Return the instance
		return newSugarInstance;
	}

	GEOMETRY_GUID CreateFullScreenQuad(const TShader& _shader)
	{
		static int FSQCounter = 0;
		TMaterial defaultMat;
 		defaultMat.shader = _shader;
 		STRING_TYPE meshName = "FSQ_";	
 		meshName += std::to_string(FSQCounter++);
 		GRAPHICS_DEBUG("Creating FSQ "<<meshName);
		ShaderManager::Instance().CreateShader(defaultMat.shader); 
		GEOMETRY_GUID guid = ResourceManager::Instance().InstanciateRunTimeGeometry(meshName, defaultMat.shader, FSQVertex, 4, FSQIndex, 2);
		TGeometry* geo = ResourceManager::Instance().RequestRuntimeGeometry(guid);
		geo->os_bb._max = bento::vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		geo->os_bb._min = -bento::vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		return guid;
	}

	TMesh* CreateSkyboxDrawable(SKYBOX_GUID _skyboxID)
	{	
		// Fetch the texture
		TSkyboxTexture* skybox = ResourceManager::Instance().RequestRuntimeSkybox(_skyboxID);
		
		// Create the shader
		TOPPING_GUID topping = TToppingLoader::Instance().FetchMaterial("skybox");
		TMaterial* mat = TToppingLoader::Instance().RequestRuntimeMaterial(topping);

 		TCubeMapInfo newCM;
		newCM.cmID = skybox->id;
		newCM.offset = 0;
		newCM.name = "skybox";
		mat->cubeMaps.push_back(newCM);
		
		// Create the geometry
		GEOMETRY_GUID fsq = CreateFullScreenQuad(mat->shader);
		return new TMesh(topping, fsq);
	}

}