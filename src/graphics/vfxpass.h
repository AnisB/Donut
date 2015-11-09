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
#include "graphics/drawable.h"
#include "graphics/pass.h"
#include "core/camera.h"
#include "core/node.h"
#include "Render/Light.h"
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
		TVFXPass();
		~TVFXPass();
		
		// Setting the pass content
		void Set(TCanvas* _canvas, TVFX* _vfx);
		void Init();
		// Setting and disabling the canvas
		void Bind();
		void Unbind();

		// Render the VFX (using the canvas data)
		void Draw(const TBufferOutput& _previousData);

		// Getting the pass output
		const TBufferOutput* GetOutput();

	private:
		// Rendering data
		TCanvas * m_canvas;
		TVFX* m_vfx;
	};
	// END CLASS DECLARATION
 }
 #endif // VFX_PASS_GRAPHICS
