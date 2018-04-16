// Library includes
#include "graphics/gbuffercanvas.h"
#include "gpu_backend/gl_factory.h"

namespace donut
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
		m_frameBuffer = gl::framebuffer::create();
		gl::framebuffer::bind(m_frameBuffer);
		// Creating the textures
		// Memory allocation
		m_output.buffers.resize(5);

		// The abledo buffer
		TTextureInfo& albedo = m_output.buffers[0];
		albedo.name = "albedo";
		albedo.type = TTextureNature::COLOR;
		albedo.offset = 0;
		gl::texture2D::create(albedo, m_width, m_height);
		gl::framebuffer::bind_texture(m_frameBuffer, albedo);

 		// The normal buffer
		TTextureInfo& normal = m_output.buffers[1];
		normal.name = "normal";
		normal.type = TTextureNature::COLOR;
		normal.offset = 1;
		gl::texture2D::create(normal, m_width, m_height);
		gl::framebuffer::bind_texture(m_frameBuffer, normal);

 		// The specular buffer
		TTextureInfo& specular = m_output.buffers[2];
		specular.name = "specular";
		specular.type = TTextureNature::COLOR;
		specular.offset = 2;
		gl::texture2D::create(specular, m_width, m_height);
		gl::framebuffer::bind_texture(m_frameBuffer, specular);

 		// Position Buffer
		TTextureInfo& position = m_output.buffers[3];
		position.name = "position";
		position.type = TTextureNature::COLOR;
		position.offset = 3;
		gl::texture2D::create(position, m_width, m_height);
		gl::framebuffer::bind_texture(m_frameBuffer, position);

 		// Depth buffer
		TTextureInfo& depth = m_output.buffers[4];
		depth.name = "depth";
		depth.type = TTextureNature::DEPTH;
		depth.offset = 4;
		gl::texture2D::create(depth, m_width, m_height);
		gl::framebuffer::bind_texture(m_frameBuffer, depth);

 		// Making sure everything is OK
		gl::framebuffer::check(m_frameBuffer);
		gl::framebuffer::unbind(m_frameBuffer);
	}

	void TGBufferCanvas::Enable()
	{
		gl::framebuffer::bind(m_frameBuffer);
		gl::framebuffer::enable_depth_test(m_frameBuffer);
		gl::framebuffer::clear(m_frameBuffer);
		gl::framebuffer::set_num_render_targets(m_frameBuffer, 4);
	}

	void TGBufferCanvas::Disable()
	{
		gl::framebuffer::disable_depth_test(m_frameBuffer);
		gl::framebuffer::unbind(m_frameBuffer);
	}
}
