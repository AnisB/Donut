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
		TSkyboxFX(const TShaderPipelineDescriptor& _shader, const GPUBackendAPI* backendAPI);
		~TSkyboxFX();
		// Init
		virtual void Init();
		void SetSkybox(CUBEMAP_GUID cubemap);
		void SetCamera(Camera* _camera);
		// Drawing it
		void Draw(std::map<std::string, TUniform>& _values, const TFrameBufferOutput& _previousData);
	protected:
		Camera* m_camera;
	};
}