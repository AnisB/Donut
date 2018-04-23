#pragma once

// Library includes
#include "graphics/shaderManager.h"
#include "graphics/material.h"
#include "gpu_backend/gpu_backend.h"
#include "resource/skybox.h"

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

 		// Load data from the asset database
		GEOMETRY_GUID fetch_geometry_id(const char* geometry_path);
		TEXTURE_GUID fetch_texture_id(const char* texture_path);
		CUBEMAP_GUID fetch_cubemap_id(const char* skybox_path);
		MATERIAL_GUID instanciate_material(const char* topping_id, const char* material_name);

		// Create temporary geometry from an egg structure
		GEOMETRY_GUID create_runtime_geometry(const char* runtime_name, const TEgg& input_geometry);

		// Access rendering data using their id (used by the rendering thread)
		GeometryObject request_runtime_geometry(GEOMETRY_GUID _geometryIndex) { return m_geometries[_geometryIndex]; }
		TMaterial& request_runtime_material(MATERIAL_GUID material_idx) { return m_materials[material_idx]; }

	protected:
		// Asset folder path
		STRING_TYPE m_rootAssetFolder;

		// Texture data
		std::map<STRING_TYPE, TEXTURE_GUID> m_textureIdentifiers;
		std::vector<TextureObject> m_textures;

		// Cubemap data
		std::map<STRING_TYPE, CUBEMAP_GUID> m_cubemapIdentifiers;
		std::vector<CubemapObject> m_cubemaps;

		// Geometry data
		std::map<STRING_TYPE, GEOMETRY_GUID> m_geometryIdentifiers;
		std::vector<GeometryObject> m_geometries;

		// Material data
		std::map<STRING_TYPE, MATERIAL_GUID> m_materialIdentifiers;
		std::vector<TMaterial> m_materials;
	};
}