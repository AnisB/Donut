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

namespace donut
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
		GEOMETRY_GUID fsqIndx = CreateFullScreenQuad(m_material.shader);
		m_fsq =  ResourceManager::Instance().RequestRuntimeGeometry(fsqIndx);
	}

	void TVFX::BindBufferOutput(std::map<STRING_TYPE, TUniformHandler>& _values, const TBufferOutput& _previous)
	{
		// Injecting frame size
 		ShaderManager::Instance().Inject<int>(m_material.shader, _previous.width, "width");
 		ShaderManager::Instance().Inject<int>(m_material.shader, _previous.height, "height");
 		// Injecting buffers
 		ShaderManager::Instance().InjectMaterial(m_material.shader, m_material);

 		for(auto& buffer : _previous.buffers)
 		{
 			ShaderManager::Instance().InjectTex(m_material.shader, buffer.texID, buffer.name, buffer.offset + m_material.textures.size() );
 		}
		for(const auto& uniform : _values)
 		{
 			const TUniformHandler& handler = uniform.second;
 			handler.Inject(m_material.shader);
 		}
 		
	}

	void TVFX::AddTexture(TTexture* parTex, const STRING_TYPE& _nameInMaterial)
 	{
		TTextureInfo newTex;
		newTex.texID = parTex->FID;
		newTex.offset = (int)m_material.textures.size();
		newTex.name = _nameInMaterial;
		m_material.textures.push_back(newTex);
 	}

 	void TVFX::AddCubeMap(TSkyboxTexture* _skybox, const STRING_TYPE& _nameInMaterial)
 	{
		TCubeMapInfo newCM;
		newCM.cmID = _skybox->id;
		newCM.offset = (int)m_material.cubeMaps.size();
		newCM.name = _nameInMaterial;
		m_material.cubeMaps.push_back(newCM);
 	}
}
