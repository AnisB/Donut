// Internal includes
#include "graphics/material.h"
#include "resource/resource_manager.h"

namespace donut
{
    void inject_material(ShaderPipelineObject program, const TMaterial& material, const GPUBackendAPI* backendAPI)
    {
		for (auto& uni : material.uniforms)
		{
			uni.inject(program, backendAPI);
		}

		for (const TTextureInfo& tex : material.textures)
		{
			TextureObject textureObject = ResourceManager::Instance().request_runtime_texture(tex.id);
			backendAPI->shader_api.inject_texture(program, textureObject, tex.offset, tex.name.c_str());
		}

		for (auto& cubemap : material.cubeMaps)
		{
			CubemapObject cubemapObject = ResourceManager::Instance().request_runtime_cubemap(cubemap.id);
			backendAPI->shader_api.inject_cubemap(program, cubemapObject, cubemap.offset, cubemap.name.c_str());
		}
    }
}