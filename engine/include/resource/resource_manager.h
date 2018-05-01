#pragma once

// Library includes
#include "graphics/shaderManager.h"
#include "graphics/material.h"
#include "gpu_backend/gpu_backend.h"
#include "resource/skybox.h"
#include "resource/asset_database.h"

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

 		bool init(const char* database_path);

 		// Create / Fetch runtime data
		GEOMETRY_GUID fetch_geometry_id(const char* geometry_path);
		TEXTURE_GUID fetch_texture_id(const char* texture_path);
		CUBEMAP_GUID fetch_cubemap_id(const char* skybox_path);
		MATERIAL_GUID instanciate_material(const char* topping_id, const char* material_name);

		// Create temporary geometry from an egg structure
		GEOMETRY_GUID create_runtime_geometry(const char* runtime_name, const TEgg& input_geometry);

		// Access rendering data using their id (used by the rendering thread)
		GeometryObject request_runtime_geometry(GEOMETRY_GUID _geometryIndex) { return m_geometries[_geometryIndex]; }
		TMaterial& request_runtime_material(MATERIAL_GUID material_idx) { return m_materials[material_idx]; }

		// Access a resource from the asset database
		template<typename T>
		bool request_asset(const char* asset_name, T& output_asset)
		{
			// Request the data from the database
			const TAsset* requested_asset = m_asset_database.request_asset(asset_name);
			if (requested_asset == nullptr) return false;

			// Deserialize the texture
			const char* raw_data = requested_asset->data.begin();
			return bento::unpack_type(raw_data, output_asset);
		}

	private:
		// Asset database
		TAssetDatabase m_asset_database;

		// Texture data
		std::map<std::string, TEXTURE_GUID> m_textureIdentifiers;
		std::vector<TextureObject> m_textures;

		// Cubemap data
		std::map<std::string, CUBEMAP_GUID> m_cubemapIdentifiers;
		std::vector<CubemapObject> m_cubemaps;

		// Geometry data
		std::map<std::string, GEOMETRY_GUID> m_geometryIdentifiers;
		std::vector<GeometryObject> m_geometries;

		// Material data
		std::map<std::string, MATERIAL_GUID> m_materialIdentifiers;
		std::vector<TMaterial> m_materials;
	};
}