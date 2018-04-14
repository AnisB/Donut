#include "resource/ResourceManager.h"
#include "resource/TextureHelpers.h"
#include "resource/sugar_loader.h"
#include "resource/toppingloader.h"
#include "resource/pipelineloader.h"
#include "resource/flourloader.h"
#include "resource/egghelpers.h"
#include "gpu_backend/gl_factory.h"

#include <fstream>
#include <sstream> 
#include <vector> 
#include <list> 

 using namespace std;
 
 namespace donut
 {
 	ResourceManager::ResourceManager()
 	: m_rootAssetFolder("./assets/")
 	{

 	}

 	ResourceManager::~ResourceManager()
 	{

 	}

	void ResourceManager::Init(const STRING_TYPE& _assertFolder)
	{
		m_rootAssetFolder = _assertFolder + "/";
		TSugarLoader::Instance().Init();
		TPipelineLoader::Instance().Init();
		TFlourLoader::Instance().Init();
		TToppingLoader::Instance().Init();
	}
 	
 	TTexture* ResourceManager::FetchTexture(const STRING_TYPE&  _textureName)
 	{
 		auto it = FTextures.find(_textureName);
 		if(it != FTextures.end())
 		{
 			it->second->FNbRef++;
 			return it->second;
 		}
 		else
 		{
 			TTexture * texture =  TextureHelpers::LoadTexture(RootAssetsFolder() + _textureName);
 			FTextures[_textureName] = texture;
 			gl::texture2D::create(*texture);
 			texture->FNbRef++;
 			return texture;
 		}
 	}

 	SKYBOX_GUID ResourceManager::FetchSkybox(const STRING_TYPE&  _skyboxFolder, const STRING_TYPE& _extension)
 	{
 		auto it = m_skyboxIdentifiers.find(_skyboxFolder);
 		if(it != m_skyboxIdentifiers.end())
 		{
 			return it->second;
 		}
 		else
 		{
 			// Read the skybox data into memory
 			TSkyboxTexture* skybox =  TextureHelpers::LoadSkybox(RootAssetsFolder() + _skyboxFolder, TextureHelpers::GetImgType(_extension));
 			
 			// Instciate the runtime data
 			gl::textureCUBE::create(*skybox);

 			// Register and return index
 			return InsertSkybox(_skyboxFolder, skybox);
 		}
 	}

	GEOMETRY_GUID ResourceManager::FetchGeometry(const TShader& parShader, const STRING_TYPE&  _fileName)
	{
		// Try to get the resource
 		auto it = m_geometryIdentifiers.find(_fileName);
 		if(it != m_geometryIdentifiers.end())
 		{
 			return it->second;
 		}

		// Load the file into memory
		TEgg* container = ReadEggFile(RelativePath(_fileName));
		assert_msg(container != nullptr, "Geomtry file couldn't be read");

		// Instanciate the runtime geometry
		GeometryObject geo_obj = gl::geometry::create_vnt(container->vertsNormalsUVs, container->nbVertices, container->faces, container->nbFaces);

		// Delete the CPU container
		delete container;

		// Append it
		return InsertGeometry(_fileName, geo_obj);
	}

	GEOMETRY_GUID ResourceManager::InstanciateRunTimeGeometry(const STRING_TYPE& _name, const TShader& parShader, float* _dataArray, int _numVert, unsigned* _indexArray, int num_faces)
	{
		GeometryObject geo_obj = gl::geometry::create_vnt(_dataArray, _numVert, _indexArray, num_faces);
		return InsertGeometry(_name, geo_obj);
	}

	GEOMETRY_GUID ResourceManager::InsertGeometry(const STRING_TYPE& _path, GeometryObject target_geometry)
	{
		// Append the Index and the geometry
		GEOMETRY_GUID geometryIndex = m_geometries.size();
		m_geometries.push_back(target_geometry);
		m_geometryIdentifiers[_path] = geometryIndex;
		return geometryIndex;
	}

	SKYBOX_GUID ResourceManager::InsertSkybox(const STRING_TYPE& _path, TSkyboxTexture* _targetSkybox)
	{
		// Append the Index and the skybox
		SKYBOX_GUID skyboxIndex = m_skyboxes.size();
		m_skyboxes.push_back(_targetSkybox);
		m_skyboxIdentifiers[_path] = skyboxIndex;
		return skyboxIndex;
	}
}