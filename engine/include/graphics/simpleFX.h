#pragma once

// Library includes
#include "graphics/visualeffect.h"
namespace donut
{
	class TSimpleFX : public TVFX
	{
	public:
		// Creation/Destruction
		TSimpleFX(const TShaderPipelineDescriptor& shader_descr, const GPUBackendAPI* backendAPI);
		~TSimpleFX();
		// Init
		virtual void Init();
		// Drawing it
		void Draw(std::map<std::string, TUniform>& _values, const TBufferOutput& _previousData);
	};
}