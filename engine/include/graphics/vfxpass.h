#pragma once

// Library includes
#include "graphics/pass.h"
#include "core/camera.h"
#include "graphics/canvas.h"
#include "graphics/visualeffect.h"

// STL includes
#include <vector>
 
 namespace donut
 {
	class TVFXPass : public TPass
	{
	public:
		// Constructor destructor
		TVFXPass(TCanvas* _canvas, TVFX* _vfx, const char* name, bento::IAllocator& allocator, const GPUBackendAPI* backendAPI);
		~TVFXPass();
		
		// Setting the pass content
		void Init();
		void SetCamera(Camera* _camera) { m_camera = _camera; }
		
		// Setting and disabling the canvas
		void Bind();
		void Unbind();

		// Render the VFX (using the canvas data)
		void Draw(const TFrameBufferOutput& _previousData);

		// Getting the pass output
		const TFrameBufferOutput* GetOutput();

	private:
		// Rendering data
		Camera * m_camera;
		TCanvas * m_canvas;
		TVFX* m_vfx;
		std::map<std::string, TUniform> m_values;
	};
	// END CLASS DECLARATION
 }