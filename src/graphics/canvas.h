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
#ifndef CANVAS_GRAPHICS_DONUT
#define CANVAS_GRAPHICS_DONUT

// Library includes
#include "graphics/common.h"
#include "graphics/shaderdata.h"
#include "graphics/material.h"
#include "resource/texture.h"

namespace Donut
{
	// Foward declaration
	struct TGeometry;


	struct TBufferOutput
	{
		int width;
		int height;
		std::vector<TTextureInfo> buffers;
	};

	// Class
	class TCanvas
	{
	public:
		// Creation
		TCanvas(int _width, int _height);
		virtual ~TCanvas();
		// Init, could be in the constructor, but whatever
		virtual void Init() =  0;
		// Enabling the canvas before drawing it
		virtual void Enable() = 0;
		// Disabling the canvas after drawing it
		virtual void Disable() = 0;
		// Returns the output of this canvas
		const TBufferOutput& Result();
		// Attaching a texture to a canvas
		void AttachTexture(TTexture* _texture, const std::string& _uniformVarName);

	protected:
		int m_width;
		int m_height;
		// GPU buffer index
		GLuint m_frameBuffer;
		// What you will get from this canvas after drawing into it
		TBufferOutput m_output;
	};
	// END CLASS DECLARATION
}
 #endif // CANVAS_GRAPHICS_DONUT
