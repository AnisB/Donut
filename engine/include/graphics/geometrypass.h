#pragma once

// Library includes
#include "graphics/drawable.h"
#include "core/camera.h"
#include "graphics/pass.h"
#include "core/node.h"
#include "render/collector.h"
#include "render/dispatcher.h"
#include "graphics/canvas.h"
#include "graphics/visualeffect.h"
#include "core/flour.h"

// STL includes
#include <vector>
 
 namespace donut
 {
	class TGeometryPass : public TPass
	{
	public:
		// Constructor destructor
		TGeometryPass(TCanvas* _canvas, TFlour* _flour, const char* name, bento::IAllocator& allocator, const GPUBackendAPI* gpuBackend);
		virtual ~TGeometryPass();
		
		void SetCamera(Camera* _camera) { m_camera = _camera; }
		// Setting the pass content
		void Init();
		// Setting and disabling the canvas
		void Bind();
		void Unbind();

		// Render the VFX (using the canvas data)
		void Draw(const TFrameBufferOutput& _previousData);

		// Getting the pass output
		const TFrameBufferOutput* GetOutput();

	private:
		// Internal data
		bento::Matrix4 m_reference;

		// Rendering data
		Camera * m_camera;
		TCanvas * m_canvas;
		TFlour* m_flour;
		TMesh* m_skyboxDrawable;
		
		// Rendering request data
		TCollector m_collector;
		TDispatcher m_dipatcher;
	};
	// END CLASS DECLARATION
 }
