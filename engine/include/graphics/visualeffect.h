#pragma once

// Library includes
#include "graphics/shader.h"
#include "graphics/canvas.h"
#include "gpu_backend/gpu_backend.h"

// STL include
#include <map>

namespace donut
{
	#define CANVAS_VERTEX_SHADER "shaders/canvas/vertex.glsl"
	#define CANVAS_FRAGMENT_SHADER "shaders/canvas/fragment.glsl"
	
	class TVFX
	{
	public:
		// Creation/Destruction
		TVFX(const TShader& _shader);
		virtual ~TVFX();
		// Init
		virtual void Init();
		// Drawing it
		virtual void Draw(std::map<STRING_TYPE, TUniformHandler>& _values, const TBufferOutput& _previousData) = 0;
		// Attaching a texture to a vfx
	 	virtual void AddTexture(TTexture* _texture, const STRING_TYPE& _nameInMaterial);
	 	virtual void AddCubeMap(TSkyboxTexture* _skybox, const STRING_TYPE& _nameInMaterial);
	protected:
		void BindBufferOutput(std::map<STRING_TYPE, TUniformHandler>& _values, const TBufferOutput& _previous);
	protected:
		// Material
		TMaterial m_material;
		// Geometry
		GeometryObject m_fsq;
	};
}
