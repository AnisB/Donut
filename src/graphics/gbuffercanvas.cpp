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
#include "gbuffercanvas.h"
#include "graphics/glfactory.h"

namespace Donut
{
	// Creation
	TGBufferCanvas::TGBufferCanvas(int _width, int _height)
	: TCanvas(_width, _height)
	{
	}
	// Deletion
	TGBufferCanvas::~TGBufferCanvas()
	{

	}

	// Inheritance exigences
	void TGBufferCanvas::Init()
	{
		// Drawable data
		m_output.width = m_width; 
		m_output.height = m_height; 

		// Creating the main frame buffer
		m_frameBuffer = CreateFrameBuffer();
		BindFrameBuffer(m_frameBuffer);
		// Creating the textures
		// Memory allocation
		m_output.buffers.resize(5);

		// The abledo buffer
		TTextureInfo& albedo = m_output.buffers[0];
		albedo.name = "albedo";
		albedo.type = TTextureNature::COLOR;
		albedo.offset = 0;
		CreateTexture(albedo, m_width, m_height);
 		BindToFrameBuffer(albedo);

 		// The normal buffer
		TTextureInfo& normal = m_output.buffers[1];
		normal.name = "normal";
		normal.type = TTextureNature::COLOR;
		normal.offset = 1;
		CreateTexture(normal, m_width, m_height);
 		BindToFrameBuffer(normal);

 		// The specular buffer
		TTextureInfo& specular = m_output.buffers[2];
		specular.name = "specular";
		specular.type = TTextureNature::COLOR;
		specular.offset = 2;
		CreateTexture(specular, m_width, m_height);
 		BindToFrameBuffer(specular);

 		// Position Buffer
		TTextureInfo& position = m_output.buffers[3];
		position.name = "position";
		position.type = TTextureNature::COLOR;
		position.offset = 3;
		CreateTexture(position, m_width, m_height);
 		BindToFrameBuffer(position);

 		// Depth buffer
		TTextureInfo& depth = m_output.buffers[4];
		depth.name = "depth";
		depth.type = TTextureNature::DEPTH;
		depth.offset = 4;
		CreateTexture(depth, m_width, m_height);
 		BindToFrameBuffer(depth);
 		// Making sure everything is OK
 		CheckFrameBuffer();
 		UnBindFrameBuffer();
	}

	void TGBufferCanvas::Enable()
	{
		glEnable(GL_DEPTH_TEST);
 		BindFrameBuffer(m_frameBuffer);
 		glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);
 		ClearBuffer();
		GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT ,GL_COLOR_ATTACHMENT3_EXT};
    	glDrawBuffers(4, buffers);
	}

	void TGBufferCanvas::Disable()
	{
		glPopAttrib();
 		UnBindFrameBuffer();
 		glDisable(GL_DEPTH_TEST);
	}
	// END CLASS DECLARATION
}
