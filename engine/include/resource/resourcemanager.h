#pragma once

// Library includes
#include "graphics/shaderManager.h"
#include "graphics/material.h"
#include "gpu_backend/gpu_backend.h"

#include "base/singleton.h"
#include "texture.h"
#include "egg.h"
#include "types.h"

// STL includes
#include <string>
#include <vector>
#include <map>

 namespace donut 
 {
 	class ResourceManager : public Singleton<ResourceManager>
 	{
 	public:
 		ResourceManager();
 		~ResourceManager();

 		void Init(const STRING_TYPE& _assertFolder);
 	// Asset folder setting
 		inline const STRING_TYPE& RootAssetsFolder() const
 		{
 			return m_rootAssetFolder;
 		}
 		inline STRING_TYPE RelativePath(const STRING_TYPE& _fileName)
 		{
 			return (m_rootAssetFolder + _fileName);
 		}

 	// Fetching methods
 		// Returns a pointer to a given texture (using its filepath)
 		// If it has not been loaded yet, it loads the texture into the CPU RAM and the GPU RAM
 		// Else it returns a pointer to what has been loaded
		TTexture* FetchTexture(const STRING_TYPE&  parTextureName);
		// Returns a identifier for the geometry that is asked for
 		// If it has not been loaded yet, it loads the geometry into the GPU RAM
 		// Else it simply returns the identifier
		GEOMETRY_GUID FetchGeometry(const TShader& parShader, const STRING_TYPE&  parObjName);
		// Returns a pointer to a given skybox (using its filepath)
 		// If it has not been loaded yet, it loads the texture into the CPU RAM and the GPU RAM
 		// Else it returns a pointer to what has been loaded
		SKYBOX_GUID FetchSkybox(const STRING_TYPE& skybox_source);
		// This function is not really supposed to be used on a perfomance oriented scene, it is a helper that is available for the user to create
		// at runtime geometries and to register them for further access (it is used to create cubes, spheres, planes, etc etc)
		// It is also used internally by the FetchGeometry method
		GEOMETRY_GUID InstanciateRunTimeGeometry(const STRING_TYPE& _name, const TShader& parShader, float* _dataArray, int _numVert, unsigned* _indexArray, int num_faces);

		// Still to refactor
		std::vector<int> LoadObjToTexture(const STRING_TYPE&  parFileName, std::vector<TTexture*>& parTexturetable);

		TSkyboxTexture* RequestRuntimeSkybox(SKYBOX_GUID _skyboxIndex) { return m_skyboxes[_skyboxIndex]; }
		GeometryObject RequestRuntimeGeometry(GEOMETRY_GUID _geometryIndex) { return m_geometries[_geometryIndex]; }

	protected:
		GEOMETRY_GUID InsertGeometry(const STRING_TYPE& _path, GeometryObject _targetGeometry);
		SKYBOX_GUID InsertSkybox(const STRING_TYPE& _folder, TSkyboxTexture* _targetSkybox);

	protected:
		// Asset folder path
		STRING_TYPE m_rootAssetFolder;

		// Data records
		std::map<STRING_TYPE, TTexture*> FTextures;

			// Skybox data
		std::map<STRING_TYPE, SKYBOX_GUID> m_skyboxIdentifiers;
		std::vector<TSkyboxTexture*> m_skyboxes;
			
			// Geometry data
		std::map<STRING_TYPE, GEOMETRY_GUID> m_geometryIdentifiers;
		std::vector<GeometryObject> m_geometries;
	};
}