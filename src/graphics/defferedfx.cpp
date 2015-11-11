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
	// Constructor
	TDefferedFX::TDefferedFX()
	: TVFX(TShader(DEFFERED_VERTEX, DEFFERED_GEOMETRY, DEFFERED_FRAGMENT))
	{

	}
	TDefferedFX::TDefferedFX(const TShader& _shader)
	: TVFX(_shader)
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

	void TDefferedFX::Draw(std::map<std::string, TUniformHandler>& _values, const TBufferOutput& _previousData)
	{
		glEnable (GL_BLEND); // --- could reject background frags!
		glBlendEquation (GL_FUNC_ADD);
		glBlendFunc (GL_ONE, GL_ONE); // addition each time
		glDisable (GL_DEPTH_TEST);
		glDepthMask (GL_FALSE);
		ShaderManager::Instance().EnableShader(m_material.shader);
		BindBufferOutput(_values, _previousData);
		foreach_macro(light, m_lights )
		{
			(*light)->InjectData(m_material.shader);
		  	m_fsq->Draw(false);
		}
 		ShaderManager::Instance().DisableShader();
		glEnable (GL_DEPTH_TEST);
		glDepthMask (GL_TRUE);
		glDisable (GL_BLEND);
		glFlush ();
	}
}
