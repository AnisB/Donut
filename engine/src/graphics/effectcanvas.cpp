// Library includes
#include "graphics/effectcanvas.h"
#include "gpu_backend/gl_factory.h"

namespace donut
{
	TEffectCanvas::TEffectCanvas(int _width, int _height, const STRING_TYPE& _outTexName)
	: TCanvas(_width, _height)
	, m_texName(_outTexName)
	{
	}

	TEffectCanvas::~TEffectCanvas()
	{

	}

	// Inheritance exigences
	void TEffectCanvas::Init()
	{
		// Drawable data
		m_output.width = m_width; 
		m_output.height = m_height; 

		// Creating the main frame buffer
		m_frameBuffer = gl::framebuffer::create();
		gl::framebuffer::bind(m_frameBuffer);
		// Creating the textures
		// Memory allocation
		m_output.buffers.resize(1);

		// The ouputed buffer
		TTextureInfo& color = m_output.buffers[0];
		color.name = m_texName;
		color.type = TTextureNature::COLOR;
		color.offset = 0;
		gl::texture2D::create(color, m_width, m_height);
		gl::framebuffer::bind_texture(m_frameBuffer, color);

 		// Making sure everything is OK
		gl::framebuffer::check(m_frameBuffer);
		gl::framebuffer::unbind(m_frameBuffer);
	}

	void TEffectCanvas::Enable()
	{
		gl::framebuffer::bind(m_frameBuffer);
		gl::framebuffer::enable_depth_test(m_frameBuffer);
		gl::framebuffer::clear(m_frameBuffer);
		gl::framebuffer::set_num_render_targets(m_frameBuffer, 1);
	}

	void TEffectCanvas::Disable()
	{
		gl::framebuffer::disable_depth_test(m_frameBuffer);
		gl::framebuffer::unbind(m_frameBuffer);
	}
}
