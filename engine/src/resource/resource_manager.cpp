#include "asset_compiler/texture_helpers.h"
#include "resource/resource_manager.h"
#include "gpu_backend/gl_factory.h"
#include "asset_compiler/asset_database_helpers.h"
#include "resource/shader_source.h"
#include	 "butter/stream.h"
#include "base/stringhelper.h"

#include <fstream>
#include <sstream> 
#include <vector> 
#include <list> 

 using namespace std;
 
 namespace donut
 {
 	ResourceManager::ResourceManager()
 	: m_asset_database(*bento::common_allocator())
 	{
 	}

 	ResourceManager::~ResourceManager()
 	{
 	}

	GEOMETRY_GUID ResourceManager::fetch_geometry_id(const char* geometry_path)
	{
		// Try to get the resource
		auto it = m_geometryIdentifiers.find(geometry_path);
		if (it != m_geometryIdentifiers.end())
		{
			return it->second;
		}

		// Request asset from database and assert on it
		TEgg tmp_egg(*bento::common_allocator());
		bool request_res = request_asset<TEgg>(geometry_path, tmp_egg);
		assert_msg(request_res, "Geometry file couldn't be read");

		// Instanciate the runtime geometry
		GeometryObject geo_obj = gl::geometry::create_vnt(tmp_egg._vert_normal_uvs.begin(), tmp_egg._vert_normal_uvs.size() / 8, (uint32_t*)tmp_egg._indexes.begin(), tmp_egg._indexes.size());

		// Create the entries in the resource manager
		uint32_t new_geometry_idx = (uint32_t)m_geometries.size();
		m_geometries.resize(new_geometry_idx + 1);
		m_geometryIdentifiers[geometry_path] = new_geometry_idx;
		m_geometries[new_geometry_idx] = geo_obj;

		return (GEOMETRY_GUID)new_geometry_idx;
	}
 	
	TEXTURE_GUID ResourceManager::fetch_texture_id(const char* texture_path)
 	{
 		auto it = m_textureIdentifiers.find(texture_path);
 		if(it != m_textureIdentifiers.end())
 		{
 			return (it->second);
 		}
 		else
 		{
			// Request asset from database and assert on it
			TTexture tmp_texture(*bento::common_allocator());
			bool request_res = request_asset<TTexture>(texture_path, tmp_texture);
			assert_msg(request_res, "Texture file couldn't be read");

			// Create the entries in the resource manager
			uint32_t new_texture_id = (uint32_t)m_textures.size();
			m_textures.resize(new_texture_id + 1);
			m_textureIdentifiers[texture_path] = new_texture_id;

			// Create a gpu texture
			m_textures[new_texture_id] = gl::texture2D::create(tmp_texture);

 			return (TEXTURE_GUID)new_texture_id;
 		}
 	}

	CUBEMAP_GUID ResourceManager::fetch_cubemap_id(const char* skybox_path)
 	{
 		auto it = m_cubemapIdentifiers.find(skybox_path);
 		if(it != m_cubemapIdentifiers.end())
 		{
			return it->second;
		}
 		else
 		{
			// Request asset from database and assert on it
			TTexture tmp_texture(*bento::common_allocator());
			bool request_res = request_asset<TTexture>(skybox_path, tmp_texture);
			assert_msg(request_res, "Texture file couldn't be read");

			// Build the skybox from the texture
			TSkybox tmp_skybox(*bento::common_allocator());
			skybox::build_from_atlas(tmp_skybox, tmp_texture);

			// Create the entries in the resource manager
			uint32_t new_cubemap_id = (uint32_t)m_cubemaps.size();
			m_cubemaps.resize(new_cubemap_id + 1);
			m_cubemapIdentifiers[skybox_path] = new_cubemap_id;

			// Create a gpu texture
			m_cubemaps[new_cubemap_id] = gl::textureCUBE::create(tmp_skybox);
 			return (CUBEMAP_GUID)new_cubemap_id;
 		}
 	}

	MATERIAL_GUID ResourceManager::instanciate_material(const char* topping_id, const char* material_name)
	{
		auto it = m_materialIdentifiers.find(material_name);
		if (it != m_materialIdentifiers.end())
		{
			return it->second;
		}
		else
		{
			// Request asset from database and assert on it
			TToppingDescriptor tmp_descriptor(*bento::common_allocator());
			bool request_res = request_asset<TToppingDescriptor>(topping_id, tmp_descriptor);
			assert_msg(request_res, "Topping asset couldn't be read");

			// Create a new material slot
			uint32_t new_mat_id = (uint32_t)m_materials.size();
			m_materials.resize(new_mat_id + 1);
			TMaterial& new_material = m_materials[new_mat_id];
			m_materialIdentifiers[material_name] = new_mat_id;

			// offset to assign the textures to the 
			int offset = 0;
			for (auto& tex : tmp_descriptor.data)
			{
				switch (tex.type)
				{
					case (uint8_t)TShaderDataType::VEC4:
					{
						TUniform uniform;
						uniform.type = TShaderDataType::VEC4;
						uniform.slot = tex.slot.c_str();
						reinterpret_cast<bento::Vector4&>(uniform.data) = convert_from_string<bento::Vector4>(tex.data.c_str());
						new_material.uniforms.push_back(uniform);
					}
					break;
					case (uint8_t)TShaderDataType::TEXTURE2D:
					{
						TEXTURE_GUID texture = ResourceManager::Instance().fetch_texture_id(tex.data.c_str());
						TTextureInfo tex_info;
						tex_info.id = texture;
						tex_info.name = tex.slot.c_str();
						tex_info.offset = offset++;
						tex_info.type = TTextureNature::COLOR;
						new_material.textures.push_back(tex_info);
					}
					break;
					case (uint8_t)TShaderDataType::CUBEMAP:
					{
						CUBEMAP_GUID cubemap = ResourceManager::Instance().fetch_cubemap_id(tex.data.c_str());
						TCubeMapInfo cubemap_info;
						cubemap_info.id = cubemap;
						cubemap_info.name = tex.slot.c_str();
						cubemap_info.offset = offset++;
						new_material.cubeMaps.push_back(cubemap_info);
					}
					break;
				}
			}

			// Load the shader into memory
			new_material.shader = ShaderManager::Instance().create_shader(tmp_descriptor.shader_pipeline);

			return (MATERIAL_GUID)new_mat_id;
		}
	}

	GEOMETRY_GUID ResourceManager::create_runtime_geometry(const char* runtime_name, const TEgg& input_geometry)
	{
		GeometryObject geo_obj = gl::geometry::create_vnt(input_geometry._vert_normal_uvs.begin(), input_geometry._vert_normal_uvs.size() / 8, (uint32_t*)input_geometry._indexes.begin(), input_geometry._indexes.size());

		uint32_t new_geometry_idx = (uint32_t)m_geometries.size();
		m_geometries.resize(new_geometry_idx + 1);
		m_geometries[new_geometry_idx] = geo_obj;
		m_geometryIdentifiers[runtime_name] = new_geometry_idx;

		return (GEOMETRY_GUID)new_geometry_idx;
	}
}