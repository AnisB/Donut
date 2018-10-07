// Library includes
#include "render/render_request.h"
#include "resource/resource_manager.h"

// Bento includes
#include "bento_math/matrix4.h"

namespace donut
{
	// Processed a render request
	void ProcessRenderRequest(const TRenderRequest& _request, std::map<std::string, TUniform>& _uniforms, const GPUBackendAPI* gpuBackend)
	{
		// Fetch the real data to process
		GeometryObject geometry = ResourceManager::Instance().request_runtime_geometry(_request.geometry);
		const TMaterial& mat = ResourceManager::Instance().request_runtime_material(_request.material);

		// Bind the shader
		gpuBackend->shader_api.bind_shader(mat.shader);

		// Draw the geometry
		inject_material(mat.shader, mat, gpuBackend);

		for(auto& uniform : _uniforms)
		{
			const TUniform& handler = uniform.second;
			handler.inject(mat.shader, gpuBackend);
		}
		// Fetch the view projection matrix
		bento::Matrix4 viewprojection;
		_uniforms["viewprojection"].get_data(viewprojection);
		bento::Matrix4 modelviewprojection = viewprojection * _request.transform;
		gpuBackend->shader_api.inject_mat4(mat.shader, modelviewprojection, "modelviewprojection");
		gpuBackend->shader_api.inject_mat4(mat.shader, _request.transform, "model");

		// Render the geometry
		gpuBackend->geometry_api.draw(geometry);


		// DIsable the shader
		gpuBackend->shader_api.unbind_shader(mat.shader);
	}
}