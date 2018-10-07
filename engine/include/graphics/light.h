#pragma once

// Internal includes
#include "gpu_backend/gpu_types.h"
#include "gpu_backend/gpu_backend.h"

// Bento includes
#include <bento_math/Vector3.h>
 
 namespace donut
 {
	struct TLight
	{
		bento::Vector3 position;
		bento::Vector4 color;
		float radius;
		float power;
	};

	void inject_light(const TLight& light, ShaderPipelineObject shader, size_t light_slot, const GPUBackendAPI* gpuBackendAPI);
 }