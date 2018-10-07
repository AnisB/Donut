
// Library includes
#include "graphics/defferedfx.h"

namespace donut
{
	#define DEFFERED_VERTEX "common/shaders/light/vertex.glsl"
	#define DEFFERED_GEOMETRY "common/shaders/light/geometry.glsl" 
	#define DEFFERED_FRAGMENT "common/shaders/light/fragment.glsl" 

	#define MAX_NB_LIGHTS 20

	// Constructor
	TDefferedFX::TDefferedFX(const GPUBackendAPI* backendAPI)
	: TVFX(TShaderPipelineDescriptor(*bento::common_allocator(), DEFFERED_VERTEX, DEFFERED_GEOMETRY, DEFFERED_FRAGMENT), backendAPI)
	, m_nbLights(0)
	{

	}

	// Destructor
	TDefferedFX::~TDefferedFX()
	{

	}

	// Init
	void TDefferedFX::Init()
	{
		TVFX::Init();
	}

	void TDefferedFX::SetLights(std::vector<TLight>& _lights)
	{
		// Setting the internal data
		m_nbLights = (uint32_t)_lights.size();
		if (!m_nbLights)
		{
			m_lights = nullptr;
		}
		else
		{
			m_lights = &_lights[0];
			// Make sure we did not explode the number of lights
			assert_msg(MAX_NB_LIGHTS >= m_nbLights, "Too many lights");
		}
	}

	void TDefferedFX::Draw(std::map<std::string, TUniform>& _values, const TFrameBufferOutput& _previousData)
	{
		// Enable the deffed shader 
		_gpuBackendAPI->shader_api.bind_shader(m_material.shader);

		// Inject the necessary data
		BindBufferOutput(_values, _previousData);

		_gpuBackendAPI->shader_api.inject_int(m_material.shader, m_nbLights, "num_lights");

		// Inject the lights
		for(uint32_t lightIndex = 0; lightIndex < m_nbLights; ++lightIndex)
		{
			inject_light(m_lights[lightIndex], m_material.shader, lightIndex, _gpuBackendAPI);
		}

		// Draw the frame
		_gpuBackendAPI->geometry_api.draw(m_fsq);

	  	// Disable the shader
		_gpuBackendAPI->shader_api.bind_shader(m_material.shader);
	}
}
