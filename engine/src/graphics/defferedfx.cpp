
// Library includes
#include "graphics/defferedfx.h"
#include "gpu_backend/gl_factory.h"

namespace donut
{
	#define DEFFERED_VERTEX "common/shaders/light/vertex.glsl"
	#define DEFFERED_GEOMETRY "common/shaders/light/geometry.glsl" 
	#define DEFFERED_FRAGMENT "common/shaders/light/fragment.glsl" 

	#define MAX_NB_LIGHTS 20

	// Constructor
	TDefferedFX::TDefferedFX()
	: TVFX(TShader(DEFFERED_VERTEX, DEFFERED_GEOMETRY, DEFFERED_FRAGMENT))
	, m_nbLights(0)
	{

	}
	TDefferedFX::TDefferedFX(const TShader& _shader)
	: TVFX(_shader)	
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
		m_nbLights = _lights.size();
		m_lights = &_lights[0];
		
		// Make sure we did not explode the number of lights
		assert_msg(MAX_NB_LIGHTS >= m_nbLights, "Too many lights");
	}

	void TDefferedFX::Draw(std::map<STRING_TYPE, TUniformHandler>& _values, const TBufferOutput& _previousData)
	{
		// Enable the deffed shader 
		ShaderManager::Instance().EnableShader(m_material.shader);

		// Inject the necessary data
		BindBufferOutput(_values, _previousData);

		ShaderManager::Instance().Inject<int>(m_material.shader, m_nbLights, "nbLights");

		// Inject the lights
		for(int lightIndex = 0; lightIndex < m_nbLights; ++lightIndex)
		{
			m_lights[lightIndex].InjectData(m_material.shader, lightIndex);
		}

		// Draw the frame
		gl::geometry::draw(m_fsq);

	  	// Disable the shader
 		ShaderManager::Instance().DisableShader();
	}
}
