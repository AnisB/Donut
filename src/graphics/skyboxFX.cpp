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
#include "skyboxfx.h"
#include "graphics/geometry.h"
#include "graphics/shadermanager.h"
#include "resource/resourcemanager.h"

namespace donut
{
	// Constructor
	TSkyboxFX::TSkyboxFX(const TShader& _shader)
	: TVFX(_shader)
	{
	}

	// Destructor
	TSkyboxFX::~TSkyboxFX()
	{

	}

	// Init
	void TSkyboxFX::Init()
	{
		TVFX::Init();
	}

	void TSkyboxFX::SetSkybox(SKYBOX_GUID _skybox) 
	{
		// Keep track of the resource
		m_skybox = _skybox;

		// Request the runtime data
		TSkyboxTexture* skybox = ResourceManager::Instance().RequestRuntimeSkybox(m_skybox);

		// Create the entry
 		TCubeMapInfo newCM;
		newCM.cmID = skybox->id;
		newCM.offset = 0;
		newCM.name = "skybox";

		// Add it to the material
		m_material.cubeMaps.push_back(newCM);
	}

	void TSkyboxFX::SetCamera(Camera* _camera)
	{
		m_camera = _camera;
	}

	void TSkyboxFX::Draw(std::map<STRING_TYPE, TUniformHandler>& _values, const TBufferOutput& _previousData)
	{
		ShaderManager::Instance().EnableShader(m_material.shader);
		BindBufferOutput(_values, _previousData);
		ShaderManager::Instance().Inject<Matrix3>(m_material.shader, m_camera->GetInverseViewMatrix(), "view_inverse");
		ShaderManager::Instance().Inject<Matrix4>(m_material.shader, m_camera->GetProjectionMatrix(), "projection");
		ShaderManager::Instance().Inject(m_material.shader, 1.0f, "near_plane");
	  	m_fsq->Draw(false);
 		ShaderManager::Instance().DisableShader();
		glFlush ();
	}
}
