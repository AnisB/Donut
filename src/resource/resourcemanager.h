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



#ifndef RESOURCE_MANAGER_DONUT
#define RESOURCE_MANAGER_DONUT

// Library includes
#include "graphics/shaderManager.h"
#include "graphics/geometry.h"
#include "graphics/material.h"

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
		SKYBOX_GUID FetchSkybox(const STRING_TYPE& _skyboxFolder, const STRING_TYPE& _extension);
		// This function is not really supposed to be used on a perfomance oriented scene, it is a helper that is available for the user to create
		// at runtime geometries and to register them for further access (it is used to create cubes, spheres, planes, etc etc)
		// It is also used internally by the FetchGeometry method
		GEOMETRY_GUID InstanciateRunTimeGeometry(const STRING_TYPE& _name, const TShader& parShader, float* _dataArray, int _numVert, unsigned* _indexArray, int num_faces);

		// Still to refactor
		std::vector<int> LoadObjToTexture(const STRING_TYPE&  parFileName, std::vector<TTexture*>& parTexturetable);

		TSkyboxTexture* RequestRuntimeSkybox(SKYBOX_GUID _skyboxIndex) { return m_skyboxes[_skyboxIndex]; }
		TGeometry* RequestRuntimeGeometry(GEOMETRY_GUID _geometryIndex) { return m_geometries[_geometryIndex]; }

	protected:
		GEOMETRY_GUID InsertGeometry(const STRING_TYPE& _path, TGeometry* _targetGeometry);
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
		std::vector<TGeometry*> m_geometries;

	};
}

#endif // RESOURCE_MANAGER_DONUT
