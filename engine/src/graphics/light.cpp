#include "graphics/light.h"
#include "base/stringhelper.h"

// Bento includes
#include <bento_math/vector4.h>

namespace donut
{
	void inject_light(const TLight& light, ShaderPipelineObject shader, size_t light_index, const GPUBackendAPI* gpuBackendAPI)
	{
		// Compute the light slot
		STRING_TYPE light_slot = "light_data[" + convert_to_string(light_index) + "]";
		gpuBackendAPI->shader_api.inject_vec3(shader, light.position, (light_slot+".position").c_str());
		gpuBackendAPI->shader_api.inject_vec4(shader, light.color , (light_slot+".color").c_str());
		gpuBackendAPI->shader_api.inject_float(shader, light.power , (light_slot+".power").c_str());
		gpuBackendAPI->shader_api.inject_float(shader, light.radius , (light_slot+".radius").c_str());
	}
 }
