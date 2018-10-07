// Library includes
#include "graphics/factory.h"
#include "core/sugarinstance.h"
#include "core/mesh.h"
#include "core/mesh.h"
#include "resource/resource_manager.h"
#include "resource/sugar_descriptor.h"
#include "core/box3.h"

// External includes
#include <float.h>

namespace donut
{
	// Cube Data
	float cubeVertexL[192] = {
	1.0f, -1.0f, -1.0f, // 0
	0.0, -1.0, 0.0,
	0.0, 0.0,

	-1.0f, -1.0f, -1.0f,// 3
	0.0, -1.0, 0.0,
	0.0, 1.0,

	1.0f, -1.0f, 1.0f,  // 1
	0.0,-1.0,0.0,
	1.0,0.0,

	-1.0f, -1.0f, 1.0f, // 2
	0.0, -1.0, 0.0,
	1.0, 1.0,

	1.0f, -1.0f, -1.0f, 
	1.0,0.0,0.0,
	0.0,0.0,

	1.0f, -1.0f, 1.0f,  // 1
	1.0,0.0,0.0,
	0.0,1.0,

  	1.0f, 1.0f, -1.0f,   // 4
	1.0,0.0,0.0,
	1.0,0.0,

	1.0f, 1.0f, 1.0f,    // 5
	1.0,0.0,0.0,
	1.0,1.0,

	1.0f, -1.0f, -1.0f,  // 0
	0.0,0.0,-1.0,
	0.0,0.0,

	-1.0f, -1.0f, -1.0f, // 3
	0.0,0.0,-1.0,
	0.0,1.0,

  	1.0f, 1.0f, -1.0f,   // 4
	0.0,0.0,-1.0,
	1.0,0.0,

	-1.0f, 1.0f, -1.0f,   // 7
	0.0,0.0,-1.0,
	1.0,1.0,

	-1.0f, 1.0f, -1.0f,
	0.0,1.0,0.0,
	0.0,0.0,

	-1.0f, 1.0f, 1.0f,
	0.0,1.0,0.0,
	0.0,1.0,

  	1.0f, 1.0f, -1.0f,   // 4
	0.0,1.0,0.0,
	1.0,0.0,

	1.0f, 1.0f, 1.0f,
	0.0,1.0,0.0,
	1.0,1.0,

	1.0f, 1.0f, 1.0f,
	0.0,0.0,1.0,
	0.0,0.0,

	1.0f, -1.0f, 1.0f,
	0.0,0.0,1.0,
	0.0,1.0,

	-1.0f, 1.0f, 1.0f,
	0.0,0.0,1.0,
	1.0,0.0,

	-1.0f, -1.0f, 1.0f,
	0.0,0.0,1.0,
	1.0,1.0,	

	-1.0f, 1.0f, 1.0f,
	-1.0,0.0,0.0,
	0.0,0.0,

	-1.0f, -1.0f, 1.0f,
	-1.0,0.0,0.0,
	0.0,1.0,

	-1.0f, 1.0f, -1.0f,
	-1.0,0.0,0.0,
	1.0,0.0,

	-1.0f, -1.0f, -1.0f,
	-1.0,0.0,0.0,
	1.0,1.0
	};

	uint32_t cubeFacesL[36] = 
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
	1.0f, 0.0f, -1.0f, // 0
	0.0,1.0,0.0,
	0.0,0.0,

	-1.0f, 0.0f, -1.0f,// 3
	0.0,1.0,0.0,
	0.0,1.0,

	1.0f, 0.0f, 1.0f,  // 1
	0.0,1.0,0.0,
	1.0,0.0,
	
	-1.0f, 0.0f, 1.0f, // 2
	0.0,1.0,0.0,
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
		0.0, 0.0, 1.0, 
		0.0,0.0,
		-1.0f, 1.0f, 0.0f, 
		0.0, 0.0, 1.0, 
		0.0,1.0,
		1.0f, -1.0f, 0.0f, 
		0.0, 0.0, 1.0, 
		1.0,0.0,
		1.0f, 1.0f, 0.0f,
		0.0, 0.0, 1.0, 
		1.0,1.0,
	};

	uint32_t FSQIndex[6] = { 
		0, 1, 2,
		1, 2, 3
	};

	TMesh* CreateCube(float _length, const std::string& _materialName)
	{
		// Counter that tracks the created cubes in this session
		static int cubeCounter = 0;

		// Creating the geometry
		TEgg egg(*bento::common_allocator());
		egg._vert_normal_uvs.resize(192);
		egg._indexes.resize(12);
		memcpy(egg._vert_normal_uvs.begin(), cubeVertexL, 192 * sizeof(float));
		memcpy(egg._indexes.begin(), cubeFacesL, 36 * sizeof(uint32_t));

		// Scale the cube by
 		for(int i = 0; i < 24; ++i)
 		{
			egg._vert_normal_uvs[8 * i] *= _length;
			egg._vert_normal_uvs[8 * i + 1] *= _length;
			egg._vert_normal_uvs[8 * i + 2] *= _length;
 		}

		// Grab the material
		MATERIAL_GUID material = ResourceManager::Instance().instanciate_material(_materialName.c_str(), _materialName.c_str());

		// Generating the geometry name
 		std::string meshName = "Cube_";
 		meshName += std::to_string(cubeCounter++);
 		
		GEOMETRY_GUID geometry = ResourceManager::Instance().create_runtime_geometry(meshName.c_str(), egg);
		
		// Create the mesh instance
		TMesh* newMesh = new TMesh(material, geometry);

		// return it
		return newMesh;
	}

    TMesh* CreatePlane(double _with, double _length, const std::string& _materialName)
	{
		// Create the geometry buffer
		static int planeCounter = 0;

		// Creating the geometry
		TEgg plane_egg(*bento::common_allocator());
		plane_egg._vert_normal_uvs.resize(32);
		plane_egg._indexes.resize(2);
		memcpy(plane_egg._vert_normal_uvs.begin(), cubeVertexL, 32 * sizeof(float));
		memcpy(plane_egg._indexes.begin(), cubeFacesL, 6 * sizeof(uint32_t));

		// Scale the plane
		for (int i = 0; i<4; ++i)
		{
			plane_egg._vert_normal_uvs[3 * i] *= (float)_with;
		}
		for (int i = 0; i<4; ++i)
		{
			plane_egg._vert_normal_uvs[3 * i + 2] *= (float)_length;
		}

 		// Generate the geometry name
 		std::string meshName = "Plane_";
 		meshName += std::to_string(planeCounter++);

		// Create the target geometry
		GEOMETRY_GUID geometry = ResourceManager::Instance().create_runtime_geometry(meshName.c_str(), plane_egg);
		MATERIAL_GUID material = ResourceManager::Instance().instanciate_material(_materialName.c_str(), _materialName.c_str());

		// Create the mesh instance
		TMesh* newMesh = new TMesh(material, geometry);

		// return it
		return newMesh;
	}

	TMesh* CreateSphere(double _radius)
	{
		assert_fail();
		return nullptr;
	}

	TSugarInstance* CreateSugarInstance(const char* sugar_name)
	{
		// Fetch the sugar descriptor
		TSugarDescriptor sugar_descr(*bento::common_allocator());
		bool request_result = ResourceManager::Instance().request_asset<TSugarDescriptor>(sugar_name, sugar_descr);
		assert_msg(request_result, "Sugar not found");

		// Create a sugar instance
		TSugarInstance* newSugarInstance = new TSugarInstance();

		// For each renderable in the renderables array
		for(auto& renderable : sugar_descr._renderables)
		{
			// Fetch the renderable descriptor
			const TRenderableDescriptor& renderableDescriptor = renderable;

			// Fetch the material
			MATERIAL_GUID material = ResourceManager::Instance().instanciate_material(renderableDescriptor.material.c_str(), renderableDescriptor.material.c_str());

			// Fetch the geometry
			GEOMETRY_GUID geometry = ResourceManager::Instance().fetch_geometry_id(renderableDescriptor.geometry.c_str());
			
			// Create the renderable mesh
			TMesh* newMesh = new TMesh(material, geometry);

			// Add the mesh to the sugar instance
			newSugarInstance->AddMesh(newMesh);
		}

		// Return the instance
		return newSugarInstance;
	}

	GEOMETRY_GUID CreateFullScreenQuad(const GPUBackendAPI* backendAPI)
	{
		static int FSQCounter = 0;
		
		// Create our geometry
		TEgg fsq_egg(*bento::common_allocator());
		fsq_egg._vert_normal_uvs.resize(32);
		fsq_egg._indexes.resize(2);
		memcpy(fsq_egg._vert_normal_uvs.begin(), FSQVertex, 32 * sizeof(float));
		memcpy(fsq_egg._indexes.begin(), FSQIndex, 6 * sizeof(uint32_t));

		// Generate a name for it
 		std::string meshName = "FSQ_";	
 		meshName += std::to_string(FSQCounter++);

		// Create it
		GEOMETRY_GUID guid = ResourceManager::Instance().create_runtime_geometry(meshName.c_str(), fsq_egg);

		// Change its bounding box so that it is infinite
		GeometryObject geo = ResourceManager::Instance().request_runtime_geometry(guid);
		TBox3 box;
		box.max = bento::vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		box.min = -bento::vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		backendAPI->geometry_api.set_bbox(geo, box);

		return guid;
	}

	TMesh* CreateSkyboxDrawable(CUBEMAP_GUID cubemap)
	{	
		static int skybox_counter = 0;

		std::string skybox_name = "skybox_";
		skybox_name += std::to_string(skybox_counter++);

		// Create the geometry
		TMesh* skybox = CreateCube(1.0f, "skybox");

		// Request the shader
		TMaterial& mat = ResourceManager::Instance().request_runtime_material(skybox->material());

		// Add it to the material
 		TCubeMapInfo newCM;
		newCM.id = cubemap;
		newCM.offset = 0;
		newCM.name = "skybox";
		mat.cubeMaps.push_back(newCM);
		mat.flags = RenderFlags::NO_CULLING;
		
		return skybox;
	}

}