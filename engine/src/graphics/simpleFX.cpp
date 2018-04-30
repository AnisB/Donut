// Library includes
#include "graphics/simplefx.h"
#include "graphics/shadermanager.h"
#include "gpu_backend/gl_factory.h"

namespace donut
{
	// Constructor
	TSimpleFX::TSimpleFX(const TShaderPipelineDescriptor& shader_descr)
	: TVFX(shader_descr)
	{

	}

	// Destructor
	TSimpleFX::~TSimpleFX()
	{

	}

	// Init
	void TSimpleFX::Init()
	{
		TVFX::Init();
	}

	void TSimpleFX::Draw(std::map<std::string, TUniform>& _values, const TBufferOutput& _previousData)
	{
		ShaderManager::Instance().EnableShader(m_material.shader);
		BindBufferOutput(_values, _previousData);
		gl::geometry::draw(m_fsq);
 		ShaderManager::Instance().DisableShader();
	}
}
