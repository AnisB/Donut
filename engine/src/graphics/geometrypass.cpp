// Libary includes
#include "graphics/geometrypass.h"
#include "graphics/factory.h"
#include "core/mesh.h"
#include "resource/resource_manager.h"

// External includes
#include <map>

 namespace donut
 {

 	//CLASS IMPLEMENTATION
	TGeometryPass::TGeometryPass(TCanvas* _canvas, TFlour* _flour)
	: m_canvas(_canvas)
	, m_flour(_flour)
	, m_reference()
	, m_camera(nullptr)
	, m_skyboxDrawable(nullptr)
	{
		// Set identifity
		SetIdentity(m_reference);
	}
	TGeometryPass::~TGeometryPass()
	{
		delete m_canvas;
		delete m_flour;
	}
	
	void TGeometryPass::Init()
	{
		// Init the canvas
		m_canvas->Init();

		// Create the drawable for the skybox if there is some
		if (m_flour->skybox != UINT32_MAX)
		{
			m_skyboxDrawable = CreateSkyboxDrawable(m_flour->skybox);
		}
	}

	void TGeometryPass::Draw(const TBufferOutput& _previousData)
	{
		// Reset the dispatcher
		m_collector.Clear();

		// Collect the requests
		if (m_skyboxDrawable)
		{
			m_skyboxDrawable->Evaluate(m_collector, m_reference);
		}

		m_flour->root->Evaluate(m_collector, m_reference);

		// Fetch the requests
		auto& requests = m_collector.Requests();

		// Do all the processings on the requests
		m_dipatcher.ProcessRequests(requests, m_camera->GetViewMatrix(), m_camera->FrusumDescriptor());

		// Fetch the uniform values from the camera
		std::map<STRING_TYPE, TUniform> values;
		m_camera->AppendUniforms(values);

		// Process eache render request 
		for(auto& request : requests)
		{
			// Process the render request
			ProcessRenderRequest(request, values);
		}
	}

	void TGeometryPass::Bind()
	{
		m_canvas->Enable();
	}
	
	const TBufferOutput* TGeometryPass::GetOutput()
	{
		return &(m_canvas->Result());
	}

	void TGeometryPass::Unbind()
	{
		m_canvas->Disable();
	}

	// END CLASS IMPLEMENTATION
 }
