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

// Library includes
#include "graphics/simplecanvas.h"
#include "graphics/glfactory.h"

namespace donut
{
	// Creation
	TSimpleCanvas::TSimpleCanvas(int _width, int _height)
	: TCanvas(_width, _height)
	{
	}
	// Deletion
	TSimpleCanvas::~TSimpleCanvas()
	{

	}

	// Inheritance exigences
	void TSimpleCanvas::Init()
	{
		// Drawable data
		m_output.width = m_width; 
		m_output.height = m_height; 

		// Creating the main frame buffer
		m_frameBuffer = CreateFrameBuffer();
		BindFrameBuffer(m_frameBuffer);
		// Creating the textures
		// Memory allocation
		m_output.buffers.resize(2);

		// The abledo buffer
		TTextureInfo& color = m_output.buffers[0];
		color.name = "canvas";
		color.type = TTextureNature::COLOR;
		color.offset = 0;
		CreateTexture(color, m_width, m_height);
 		BindToFrameBuffer(color);

 		// Depth buffer
		TTextureInfo& depth = m_output.buffers[1];
		depth.name = "depth";
		depth.type = TTextureNature::DEPTH;
		depth.offset = 1;
		CreateTexture(depth, m_width, m_height);
 		BindToFrameBuffer(depth);
 		// Making sure everything is OK
 		CheckFrameBuffer();
 		UnBindFrameBuffer();
	}

	void TSimpleCanvas::Enable()
	{
		glEnable(GL_DEPTH_TEST);
 		BindFrameBuffer(m_frameBuffer);
 		glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);
 		ClearBuffer();
		GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT};
    	glDrawBuffers(1, buffers);
	}

	void TSimpleCanvas::Disable()
	{
		glPopAttrib();
 		UnBindFrameBuffer();
 		glDisable(GL_DEPTH_TEST);
	}
	// END CLASS DECLARATION
}
