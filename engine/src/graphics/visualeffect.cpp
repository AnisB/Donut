// Library includes
#include "graphics/visualeffect.h"
#include "resource/resource_manager.h"
#include "graphics/factory.h"

namespace donut
{
	// Constructor
	TVFX::TVFX(const TShaderPipelineDescriptor& descriptor, const GPUBackendAPI* backendAPI)
	: m_fsq(0)
	, _gpuBackendAPI(backendAPI)
	{
		m_material.shader = _gpuBackendAPI->shader_api.create_shader(descriptor);
	}

	// Destructor
	TVFX::~TVFX()
	{

	}

	// Init
	void TVFX::Init()
	{
		GEOMETRY_GUID fsqIndx = CreateFullScreenQuad(_gpuBackendAPI);
		m_fsq = ResourceManager::Instance().request_runtime_geometry(fsqIndx);
	}

	void TVFX::BindBufferOutput(std::map<std::string, TUniform>& _values, const TFrameBufferOutput& _previous)
	{
		// Injecting frame size
		_gpuBackendAPI->shader_api.inject_int(m_material.shader, _previous.width, "width");
		_gpuBackendAPI->shader_api.inject_int(m_material.shader, _previous.height, "height");

 		// Injecting buffers
		inject_material(m_material.shader, m_material, _gpuBackendAPI);

 		for(auto& buffer : _previous.buffers)
 		{
			TextureObject textureObject = ResourceManager::Instance().request_runtime_texture(buffer.id);
			_gpuBackendAPI->shader_api.inject_texture(m_material.shader, textureObject, buffer.offset + m_material.textures.size(), buffer.name.c_str());
 		}

		for(const auto& uniform : _values)
 		{
 			const TUniform& handler = uniform.second;
 			handler.inject(m_material.shader, _gpuBackendAPI);
 		}
	}

	void TVFX::AddTexture(TEXTURE_GUID texture_id, const std::string& _nameInMaterial)
 	{
		TTextureInfo newTex;
		newTex.id = texture_id;
		newTex.offset = (int)m_material.textures.size();
		newTex.name = _nameInMaterial;
		m_material.textures.push_back(newTex);
 	}

 	void TVFX::AddCubeMap(CUBEMAP_GUID skybox_id, const std::string& _nameInMaterial)
 	{
		TCubeMapInfo newCM;
		newCM.id = skybox_id;
		newCM.offset = (int)m_material.cubeMaps.size();
		newCM.name = _nameInMaterial;
		m_material.cubeMaps.push_back(newCM);
 	}
}
