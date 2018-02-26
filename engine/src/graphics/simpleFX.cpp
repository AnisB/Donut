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
#include "graphics/simplefx.h"
#include "graphics/geometry.h"
#include "graphics/shadermanager.h"

namespace donut
{
	// Constructor
	TSimpleFX::TSimpleFX(const STRING_TYPE& _vertex, const STRING_TYPE& _fragment)
	: TVFX(TShader(_vertex, _fragment))
	{

	}
	TSimpleFX::TSimpleFX(const TShader& _shader)
	: TVFX(_shader)
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

	void TSimpleFX::Draw(std::map<STRING_TYPE, TUniformHandler>& _values, const TBufferOutput& _previousData)
	{
		ShaderManager::Instance().EnableShader(m_material.shader);
		BindBufferOutput(_values, _previousData);
	  	m_fsq->Draw(false);
 		ShaderManager::Instance().DisableShader();
		glFlush ();
	}
}
