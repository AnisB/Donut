/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/


#ifndef GEOMETRY_PASS_GRAPHICS
#define GEOMETRY_PASS_GRAPHICS


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
 
 namespace Donut
 {
	class TGeometryPass : public TPass
	{
	public:
		// Constructor destructor
		TGeometryPass(TCanvas* _canvas, TFlour* _flour);
		virtual ~TGeometryPass();
		
		void SetCamera(Camera* _camera) { m_camera = _camera; }
		// Setting the pass content
		void Init();
		// Setting and disabling the canvas
		void Bind();
		void Unbind();

		// Render the VFX (using the canvas data)
		void Draw(const TBufferOutput& _previousData);

		// Getting the pass output
		const TBufferOutput* GetOutput();

	private:
		// Internal data
		Matrix4 m_reference;

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
 #endif // GEOMETRY_PASS_GRAPHICS
