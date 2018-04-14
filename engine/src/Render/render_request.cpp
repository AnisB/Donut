// Library includes
#include "render/render_request.h"
#include "resource/resourcemanager.h"
#include "resource/toppingloader.h"
#include "gpu_backend/gl_factory.h"

namespace donut
{
	// Processed a render request
	void ProcessRenderRequest(const TRenderRequest& _request, std::map<STRING_TYPE, TUniformHandler>& _uniforms)
	{
		// Fetch the real data to process
		GeometryObject geometry = ResourceManager::Instance().RequestRuntimeGeometry(_request.geometry);
		const TMaterial* mat = TToppingLoader::Instance().RequestRuntimeMaterial(_request.topping);

		// Bind the shader
		const TShader& targetShader = mat->shader;
		ShaderManager::Instance().EnableShader(targetShader);

		// Draw the geometry
		ShaderManager::Instance().InjectMaterial(targetShader, *mat);
		for(auto& uniform : _uniforms)
		{
			const TUniformHandler& handler = uniform.second;
			handler.Inject(targetShader);
		}
		// Fetch the view projection matrix
		const bento::Matrix4& viewprojection = _uniforms["viewprojection"].GetValue<bento::Matrix4>();
		ShaderManager::Instance().Inject<bento::Matrix4>(targetShader, viewprojection * _request.transform, "modelviewprojection");
		ShaderManager::Instance().Inject<bento::Matrix4>(targetShader, _request.transform, "model");

		// Render the geometry
		gl::geometry::draw(geometry);

		// DIsable the shader
		ShaderManager::Instance().DisableShader();
	}
}