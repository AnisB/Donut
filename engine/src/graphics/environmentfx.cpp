// Library includes
#include "graphics/environmentfx.h"
#include "gpu_backend/gl_factory.h"

namespace donut
{
	const char* ENVIRONMENT_VERTEX = "common/shaders/ssfx/sh/vertex.glsl";
	const char* ENVIRONMENT_FRAGMENT = "common/shaders/ssfx/sh/fragment.glsl";

	// Constructor
	TEnvironmentFX::TEnvironmentFX()
	: TVFX(TShaderPipelineDescriptor(ENVIRONMENT_VERTEX, ENVIRONMENT_FRAGMENT))
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

	void TEnvironmentFX::Draw(std::map<STRING_TYPE, TUniform>& _values, const TBufferOutput& _previousData)
	{
		ShaderManager::Instance().EnableShader(m_material.shader);
		BindBufferOutput(_values, _previousData);
		m_SH->InjectData(m_material.shader);
		gl::geometry::draw(m_fsq);
 		ShaderManager::Instance().DisableShader();
	}
}
