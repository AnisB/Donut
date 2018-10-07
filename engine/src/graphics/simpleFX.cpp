// Library includes
#include "graphics/simplefx.h"

namespace donut
{
	// Constructor
	TSimpleFX::TSimpleFX(const TShaderPipelineDescriptor& shader_descr, const GPUBackendAPI* backendAPI)
	: TVFX(shader_descr, backendAPI)
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
		_gpuBackendAPI->shader_api.bind_shader(m_material.shader);
		BindBufferOutput(_values, _previousData);
		_gpuBackendAPI->geometry_api.draw(m_fsq);
		_gpuBackendAPI->shader_api.unbind_shader(m_material.shader);
	}
}
