/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/

// Library includes
#include "defferedfx.h"
#include "base/macro.h"
#include "graphics/geometry.h"

namespace Donut
{
	#define DEFFERED_VERTEX "shaders/light/vertex.glsl"
	#define DEFFERED_GEOMETRY "shaders/light/geometry.glsl" 
	#define DEFFERED_FRAGMENT "shaders/light/fragment.glsl" 

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

	void TDefferedFX::SetLights(std::vector<TLight*>& _lights)
	{
		// Setting the internal data
		m_nbLights = _lights.size();
		m_lights = _lights;
		
		// Make sure we did not explode the number of lights
		ASSERT_MSG_NO_RELEASE(MAX_NB_LIGHTS >= m_nbLights, "Too many lights");
	}

	void TDefferedFX::Draw(std::map<std::string, TUniformHandler>& _values, const TBufferOutput& _previousData)
	{
		// Enable the deffed shader 
		ShaderManager::Instance().EnableShader(m_material.shader);

		// Inject the necessary data
		BindBufferOutput(_values, _previousData);

		ShaderManager::Instance().Inject<int>(m_material.shader, m_nbLights, "nbLights");

		// Inject the lights
		for(int lightIndex = 0; lightIndex < m_nbLights; ++lightIndex)
		{
			m_lights[lightIndex]->InjectData(m_material.shader, lightIndex);
		}

		// Draw the frame
	  	m_fsq->Draw(false);

	  	// Disable the shader
 		ShaderManager::Instance().DisableShader();
	}
}
