// Library includes
#include "graphics/simplecanvas.h"
#include "gpu_backend/gl_factory.h"

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
		m_frameBuffer = gl::framebuffer::create();
		gl::framebuffer::bind(m_frameBuffer);
		// Creating the textures
		// Memory allocation
		m_output.buffers.resize(2);

		// The abledo buffer
		TTextureInfo& color = m_output.buffers[0];
		color.name = "canvas";
		color.type = TTextureNature::COLOR;
		color.offset = 0;
		gl::texture2D::create(color, m_width, m_height);
		gl::framebuffer::bind_texture(color);

 		// Depth buffer
		TTextureInfo& depth = m_output.buffers[1];
		depth.name = "depth";
		depth.type = TTextureNature::DEPTH;
		depth.offset = 1;
		gl::texture2D::create(depth, m_width, m_height);
		gl::framebuffer::bind_texture(depth);
		// Making sure everything is OK
		gl::framebuffer::check();
		gl::framebuffer::unbind();
	}

	void TSimpleCanvas::Enable()
	{
		gl::framebuffer::bind(m_frameBuffer);
		gl::framebuffer::enable_depth_test(m_frameBuffer);
		gl::framebuffer::clear(m_frameBuffer);
		gl::framebuffer::set_num_render_targets(1);
	}

	void TSimpleCanvas::Disable()
	{
		gl::framebuffer::disable_depth_test(m_frameBuffer);
		gl::framebuffer::unbind();
	}
}
