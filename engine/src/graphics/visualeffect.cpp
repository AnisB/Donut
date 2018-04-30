// Library includes
#include "graphics/visualeffect.h"
#include "graphics/shadermanager.h"
#include "resource/resource_manager.h"
#include "graphics/factory.h"

namespace donut
{
	// Constructor
	TVFX::TVFX(const TShaderPipelineDescriptor& descriptor)
	: m_fsq(0)
	{
		m_material.shader = ShaderManager::Instance().create_shader(nullptr, nullptr, nullptr, nullptr, nullptr);
	}

	// Destructor
	TVFX::~TVFX()
	{

	}

	// Init
	void TVFX::Init()
	{
		GEOMETRY_GUID fsqIndx = CreateFullScreenQuad();
		m_fsq = ResourceManager::Instance().request_runtime_geometry(fsqIndx);
	}

	void TVFX::BindBufferOutput(std::map<std::string, TUniform>& _values, const TBufferOutput& _previous)
	{
		// Injecting frame size
 		ShaderManager::Instance().Inject<int>(m_material.shader, _previous.width, "width");
 		ShaderManager::Instance().Inject<int>(m_material.shader, _previous.height, "height");
 		// Injecting buffers
 		ShaderManager::Instance().InjectMaterial(m_material.shader, m_material);

 		for(auto& buffer : _previous.buffers)
 		{
 			ShaderManager::Instance().InjectTex(m_material.shader, buffer.id, buffer.name.c_str(), buffer.offset + m_material.textures.size() );
 		}

		for(const auto& uniform : _values)
 		{
 			const TUniform& handler = uniform.second;
 			handler.inject(m_material.shader);
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
