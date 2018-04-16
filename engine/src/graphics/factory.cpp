// Library includes
#include "graphics/factory.h"
#include "core/sugarinstance.h"
#include "core/mesh.h"
#include "core/mesh.h"
#include "resource/sugar_loader.h"
#include "resource/resourcemanager.h"
#include "resource/toppingloader.h"
#include "core/box3.h"
#include "gpu_backend/gl_factory.h"

// External includes
#include <float.h>

namespace donut
{
	// Cube Data
	float cubeVertexL[216] = {
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

	unsigned int icubeFacesL[36] =
	{
		0, 2, 1,
		1, 3, 2,
		4, 6, 5,
		5, 7, 6,
		8, 10, 9,
		9, 11, 10,
		12, 14, 13,
		13, 15, 14,
		16, 18, 17,
		17, 19, 18,
		20, 22, 21,
		21, 23, 22
	};


	// Plane Data
	float planeVertexBuffer[32] = {
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
	float FSQVertex[32] = {
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
	uint32_t FSQIndex[6] = { 
		0, 1, 2,
		1, 2, 3
	};

	TMesh* CreateCube(float _length, STRING_TYPE _materialName, bool inside = false)
	{
		static int cubeCounter = 0;
 		float data[216];
 		memcpy(&data ,&cubeVertexL, 216*sizeof(float));
 		for(int i = 0; i<72; ++i)
 		{
 			data[i] *= _length;
 		}

		TOPPING_GUID topping = TToppingLoader::Instance().FetchMaterial(_materialName);
		const TMaterial* mat = TToppingLoader::Instance().RequestRuntimeMaterial(topping);

		// Generating the geometry name
 		STRING_TYPE meshName = "Cube_";
 		meshName += std::to_string(cubeCounter++);
 		
 		// Creating the geometry
		GEOMETRY_GUID geometry = ResourceManager::Instance().InstanciateRunTimeGeometry(meshName, mat->shader, data, 24, inside ? icubeFacesL: cubeFacesL, 12);
		
		// Create the mesh instance
		TMesh* newMesh = new TMesh(topping, geometry);

		// return it
		return newMesh;
	}

    TMesh* CreatePlane(double _with, double _length, STRING_TYPE _materialName)
	{
		// Create the geometry buffer
		static int planeCounter = 0;
		float data[32];
 		memcpy(&data ,&planeVertexBuffer, 32*sizeof(float));
 		for(int i = 0; i<4; ++i)
 		{
 			data[3*i]*=(float)_with;
 		}
 		for(int i = 0; i<4; ++i)
 		{
 			data[3*i+2]*=(float)_length;
 		}

 		// Generate the geometry name
 		STRING_TYPE meshName = "Plane_";
 		meshName += std::to_string(planeCounter++);

		TOPPING_GUID topping = TToppingLoader::Instance().FetchMaterial(_materialName);
		const TMaterial* mat = TToppingLoader::Instance().RequestRuntimeMaterial(topping);

		// Create the target geometry
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
 		std::string meshName = "FSQ_";	
 		meshName += std::to_string(FSQCounter++);
		ShaderManager::Instance().CreateShader(defaultMat.shader); 
		GEOMETRY_GUID guid = ResourceManager::Instance().InstanciateRunTimeGeometry(meshName, defaultMat.shader, FSQVertex, 4, FSQIndex, 2);
		GeometryObject geo = ResourceManager::Instance().RequestRuntimeGeometry(guid);
		TBox3 box;
		box._max = bento::vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		box._min = -bento::vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		gl::geometry::set_bbox(geo, box);
		return guid;
	}

	TMesh* CreateSkyboxDrawable(SKYBOX_GUID _skyboxID)
	{	
		// Create the geometry
		TMesh* skybox = CreateCube(10.0f, "skybox", true);

		// Request the shader
		TOPPING_GUID topping = TToppingLoader::Instance().FetchMaterial("skybox");
		TMaterial* mat = TToppingLoader::Instance().RequestRuntimeMaterial(topping);

		// Fetch the texture
		TSkyboxTexture* skybox_tex = ResourceManager::Instance().RequestRuntimeSkybox(_skyboxID);

		// Add it to the material
 		TCubeMapInfo newCM;
		newCM.cmID = skybox_tex->tex_id;
		newCM.offset = 0;
		newCM.name = "skybox";
		mat->cubeMaps.push_back(newCM);
		mat->flags = RenderFlags::NO_CULLING;
		
		return skybox;
	}

}