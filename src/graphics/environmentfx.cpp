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
#include "environmentfx.h"
#include "base/macro.h"
#include "graphics/geometry.h"

namespace Donut
{
	#define ENVIRONMENT_VERTEX "common/shaders/ssfx/sh/vertex.glsl"
	#define ENVIRONMENT_FRAGMENT "common/shaders/ssfx/sh/fragment.glsl" 
	// Constructor
	TEnvironmentFX::TEnvironmentFX()
	: TVFX(TShader(ENVIRONMENT_VERTEX, ENVIRONMENT_FRAGMENT))
	{

	}
	TEnvironmentFX::TEnvironmentFX(const TShader& _shader)
	: TVFX(_shader)
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

	void TEnvironmentFX::Draw(std::map<std::string, TUniformHandler>& _values, const TBufferOutput& _previousData)
	{
		ShaderManager::Instance().EnableShader(m_material.shader);
		BindBufferOutput(_values, _previousData);
		m_SH->InjectData(m_material.shader);
		m_fsq->Draw(false);
 		ShaderManager::Instance().DisableShader();
		glFlush ();
	}
}
