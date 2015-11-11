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
#include "visualeffect.h"
#include "graphics/shadermanager.h"
#include "resource/resourcemanager.h"
#include "graphics/factory.h"
#include "base/macro.h"

namespace Donut
{
	// Constructor
	TVFX::TVFX(const TShader& _shader)
	: m_fsq(nullptr)
	{
		m_material.shader =  _shader;
	}

	// Destructor
	TVFX::~TVFX()
	{

	}

	// Init
	void TVFX::Init()
	{
		ShaderManager::Instance().CreateShader(m_material.shader);
		m_fsq = CreateFullScreenQuad(m_material.shader);
	}

	void TVFX::BindBufferOutput(std::map<std::string, TUniformHandler>& _values, const TBufferOutput& _previous)
	{
		// Injecting frame size
 		ShaderManager::Instance().Inject<int>(m_material.shader, _previous.width, "width");
 		ShaderManager::Instance().Inject<int>(m_material.shader, _previous.height, "height");
 		// Injecting buffers
 		ResourceManager::Instance().BindMaterial(m_material.shader, m_material);

 		foreach_macro(buffer, _previous.buffers)
 		{
 			ShaderManager::Instance().InjectTex(m_material.shader, buffer->texID, buffer->name, buffer->offset + m_material.textures.size() );
 		}
		foreach_macro(uniform, _values)
 		{
 			TUniformHandler& handler = uniform->second;
 			handler.Inject(m_material.shader);
 		}
 		
	}

	void TVFX::AddTexture(TTexture* parTex, const std::string& parName)
 	{
 		TTextureInfo newTex;
		newTex.texID = parTex->FID;
		newTex.offset = (int)m_material.textures.size();
		newTex.name = parName;
 		m_material.textures.push_back(newTex);
 	}
}
