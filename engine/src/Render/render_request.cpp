// Library includes
#include "render/render_request.h"
#include "resource/resourcemanager.h"
#include "resource/toppingloader.h"

namespace donut
{
	// Processed a render request
	void ProcessRenderRequest(const TRenderRequest& _request, std::map<STRING_TYPE, TUniformHandler>& _uniforms)
	{
		// Fetch the real data to process
		TGeometry* geom = ResourceManager::Instance().RequestRuntimeGeometry(_request.geometry);
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
		const Matrix4& viewprojection = _uniforms["viewprojection"].GetValue<Matrix4>();
		ShaderManager::Instance().Inject<Matrix4>(targetShader, viewprojection * _request.transform, "modelviewprojection");
		ShaderManager::Instance().Inject<Matrix4>(targetShader, _request.transform, "model");

		geom->Draw(targetShader.FIsTesselated);

		// DIsable the shader
		ShaderManager::Instance().DisableShader();
	}
}