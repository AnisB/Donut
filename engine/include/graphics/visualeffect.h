#pragma once

// Library includes
#include "graphics/shader.h"
#include "graphics/canvas.h"
#include "gpu_backend/gpu_backend.h"
#include "resource/resource_manager.h"

// STL include
#include <map>

namespace donut
{
	class TVFX
	{
	public:
		// Creation/Destruction
		TVFX(const TShaderPipelineDescriptor& descriptor);
		virtual ~TVFX();
		// Init
		virtual void Init();
		// Drawing it
		virtual void Draw(std::map<STRING_TYPE, TUniform>& _values, const TBufferOutput& _previousData) = 0;
		// Attaching a texture to a vfx
	 	virtual void AddTexture(TEXTURE_GUID texture_id, const STRING_TYPE& _nameInMaterial);
	 	virtual void AddCubeMap(CUBEMAP_GUID cubemap_id, const STRING_TYPE& _nameInMaterial);
	protected:
		void BindBufferOutput(std::map<STRING_TYPE, TUniform>& _values, const TBufferOutput& _previous);
	protected:
		// Material
		TMaterial m_material;
		// Geometry
		GeometryObject m_fsq;
	};
}
