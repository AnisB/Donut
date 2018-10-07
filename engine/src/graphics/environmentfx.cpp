// Library includes
#include "graphics/environmentfx.h"

namespace donut
{
	const char* ENVIRONMENT_VERTEX = "common/shaders/ssfx/sh/vertex.glsl";
	const char* ENVIRONMENT_FRAGMENT = "common/shaders/ssfx/sh/fragment.glsl";

	// Constructor
	TEnvironmentFX::TEnvironmentFX(const GPUBackendAPI* gpuBackendAPI)
	: TVFX(TShaderPipelineDescriptor(*bento::common_allocator(), ENVIRONMENT_VERTEX, ENVIRONMENT_FRAGMENT), gpuBackendAPI)
	{

	}

	// Destructor
	TEnvironmentFX::~TEnvironmentFX()
	{

	}

	// Init
	void TEnvironmentFX::Init()
	{
		TVFX::Init();
	}

	void TEnvironmentFX::Draw(std::map<std::string, TUniform>& _values, const TFrameBufferOutput& _previousData)
	{
		_gpuBackendAPI->shader_api.bind_shader(m_material.shader);
		BindBufferOutput(_values, _previousData);
		m_SH->InjectData(m_material.shader, _gpuBackendAPI);
		_gpuBackendAPI->geometry_api.draw(m_fsq);
		_gpuBackendAPI->shader_api.unbind_shader(m_material.shader);
	}
}
