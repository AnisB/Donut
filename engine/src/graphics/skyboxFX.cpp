// Library includes
#include "graphics/skyboxfx.h"
#include "graphics/shadermanager.h"
#include "resource/resourcemanager.h"
#include "gpu_backend/gl_factory.h"

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

	void TSkyboxFX::SetSkybox(TSkyboxTexture* skybox)
	{
		// Create the entry
 		TCubeMapInfo newCM;
		newCM.cmID = skybox->tex_id;
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
		ShaderManager::Instance().Inject<bento::Matrix3>(m_material.shader, m_camera->GetInverseViewMatrix(), "view_inverse");
		ShaderManager::Instance().Inject<bento::Matrix4>(m_material.shader, m_camera->GetProjectionMatrix(), "projection");
		ShaderManager::Instance().Inject(m_material.shader, 1.0f, "near_plane");
		gl::geometry::draw(m_fsq);
 		ShaderManager::Instance().DisableShader();
	}
}
