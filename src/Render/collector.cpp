// Library include
#include "base/macro.h"
#include "collector.h"
#include "graphics/material.h"
#include "resource/resourcemanager.h"

namespace Donut
{
	// Processed a render request
	void ProcessRenderRequest(const TRenderRequest& _request, std::map<std::string, TUniformHandler>& _uniforms)
	{
		// Bind the shader
		const TShader& targetShader = _request.material->shader;
		ShaderManager::Instance().EnableShader(targetShader);

		// Draw the geometry
		ShaderManager::Instance().InjectMaterial(targetShader, *_request.material);
		foreach_macro(uniform, _uniforms)
		{
			const TUniformHandler& handler = uniform->second;
			handler.Inject(targetShader);
		}
		// Fetch the view projection matrix
		const Matrix4& viewprojection = _uniforms["viewprojection"].GetValue<Matrix4>();	
		ShaderManager::Instance().Inject<Matrix4>(targetShader, viewprojection * _request.transform,"modelviewprojection");
		ShaderManager::Instance().Inject<Matrix4>(targetShader, _request.transform, "model");

		TGeometry* geom = ResourceManager::Instance().RequestRuntimeGeometry(_request.geometry);
		geom->Draw(targetShader.FIsTesselated);

		// DIsable the shader
		ShaderManager::Instance().DisableShader();
	}

	TCollector::TCollector()
	{
		// Nothing to do
	}

	TCollector::~TCollector()
	{
		// Nothing to do
	}

	// Clears the render request queue
	void TCollector::Clear()
	{
		m_requests.clear();
	}
}