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


#ifndef VFX_PASS_GRAPHICS
#define VFX_PASS_GRAPHICS


// Library includes
#include "graphics/pass.h"
#include "core/camera.h"
#include "graphics/canvas.h"
#include "graphics/visualeffect.h"

// STL includes
#include <vector>
 
 namespace Donut
 {
	class TVFXPass : public TPass
	{
	public:
		// Constructor destructor
		TVFXPass(TCanvas* _canvas, TVFX* _vfx);
		~TVFXPass();
		
		// Setting the pass content
		void Init();
		void SetCamera(Camera* _camera) { m_camera = _camera; }
		
		// Setting and disabling the canvas
		void Bind();
		void Unbind();

		// Render the VFX (using the canvas data)
		void Draw(const TBufferOutput& _previousData);

		// Getting the pass output
		const TBufferOutput* GetOutput();

	private:
		// Rendering data
		Camera * m_camera;
		TCanvas * m_canvas;
		TVFX* m_vfx;
	};
	// END CLASS DECLARATION
 }
 #endif // VFX_PASS_GRAPHICS
