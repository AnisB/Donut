// Library includes
#include "graphics/skyboxfx.h"
#include "resource/resource_manager.h"

namespace donut
{
	// Constructor
	TSkyboxFX::TSkyboxFX(const TShaderPipelineDescriptor& _shader, const GPUBackendAPI* backendAPI)
	: TVFX(_shader, backendAPI)
	{
	}

	// Destructor
	TSkyboxFX::~TSkyboxFX()
	{

	}

	// Init
	void TSkyboxFX::Init()
	{
		TVFX::Init();
	}

	void TSkyboxFX::SetSkybox(CUBEMAP_GUID cubemap)
	{
		// Create the entry
 		TCubeMapInfo newCM;
		newCM.id = cubemap;
		newCM.offset = 0;
		newCM.name = "skybox";

		// Add it to the material
		m_material.cubeMaps.push_back(newCM);
	}

	void TSkyboxFX::SetCamera(Camera* _camera)
	{
		m_camera = _camera;
	}

	void TSkyboxFX::Draw(std::map<std::string, TUniform>& _values, const TBufferOutput& _previousData)
	{
		_gpuBackendAPI->shader_api.bind_shader(m_material.shader);
		BindBufferOutput(_values, _previousData);
		_gpuBackendAPI->shader_api.inject_mat3(m_material.shader, m_camera->GetInverseViewMatrix(), "view_inverse");
		_gpuBackendAPI->shader_api.inject_mat4(m_material.shader, m_camera->GetProjectionMatrix(), "projection");
		_gpuBackendAPI->shader_api.inject_float(m_material.shader, 1.0f, "near_plane");
		_gpuBackendAPI->geometry_api.draw(m_fsq);
		_gpuBackendAPI->shader_api.unbind_shader(m_material.shader);
	}
}
