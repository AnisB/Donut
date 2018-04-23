#pragma once

// Library includes
#include "graphics/visualeffect.h"
#include "core/camera.h"
#include "core/mesh.h"

namespace donut
{
	class TSkyboxFX : public TVFX
	{
	public:
		// Creation/Destruction
		TSkyboxFX(const TShaderPipelineDescriptor& _shader);
		~TSkyboxFX();
		// Init
		virtual void Init();
		void SetSkybox(CUBEMAP_GUID cubemap);
		void SetCamera(Camera* _camera);
		// Drawing it
		void Draw(std::map<STRING_TYPE, TUniform>& _values, const TBufferOutput& _previousData);
	protected:
		Camera* m_camera;
	};
}