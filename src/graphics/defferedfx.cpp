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
	// Constructor
	TDefferedFX::TDefferedFX()
	: TVFX(TShader(CANVAS_VERTEX_SHADER, CANVAS_FRAGMENT_SHADER))
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

	void TDefferedFX::Draw(const TBufferOutput& _previous)
	{
		glEnable (GL_BLEND); // --- could reject background frags!
		glBlendEquation (GL_FUNC_ADD);
		glBlendFunc (GL_ONE, GL_ONE); // addition each time

		glDisable (GL_DEPTH_TEST);
		glDepthMask (GL_FALSE);

		BindBufferOutput(_previous);
		foreach_macro(light, m_lights )
		{

			(*light)->Bind();
			(*light)->InjectData();
		  	m_fsq->Draw(false);
			(*light)->Unbind();
		}
		glEnable (GL_DEPTH_TEST);
		glDepthMask (GL_TRUE);
		glDisable (GL_BLEND);
		glFlush ();
	}
}
