// Library includes
#include "render/render_request.h"
#include "resource/resource_manager.h"
#include "resource/toppingloader.h"
#include "gpu_backend/gl_factory.h"

namespace donut
{
	// Processed a render request
	void ProcessRenderRequest(const TRenderRequest& _request, std::map<STRING_TYPE, TUniform>& _uniforms)
	{
		// Fetch the real data to process
		GeometryObject geometry = ResourceManager::Instance().request_runtime_geometry(_request.geometry);
		const TMaterial& mat = ResourceManager::Instance().request_runtime_material(_request.material);

		// Bind the shader
		ShaderManager::Instance().EnableShader(mat.shader);

		// Draw the geometry
		ShaderManager::Instance().InjectMaterial(mat.shader, mat);
		for(auto& uniform : _uniforms)
		{
			const TUniform& handler = uniform.second;
			handler.inject(mat.shader);
		}
		// Fetch the view projection matrix
		bento::Matrix4 viewprojection;
		_uniforms["viewprojection"].get_data(viewprojection);

		ShaderManager::Instance().Inject<bento::Matrix4>(mat.shader, viewprojection * _request.transform, "modelviewprojection");
		ShaderManager::Instance().Inject<bento::Matrix4>(mat.shader, _request.transform, "model");

		// Render the geometry
		gl::geometry::draw(geometry);

		// DIsable the shader
		ShaderManager::Instance().DisableShader();
	}
}