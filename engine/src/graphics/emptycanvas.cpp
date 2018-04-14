// Library includes
#include "graphics/emptycanvas.h"
#include "gpu_backend/gl_factory.h"

namespace donut
{
	// Creation
	TEmptyCanvas::TEmptyCanvas(int _width, int _height)
	: TCanvas(_width, _height)
	{
	}
	// Deletion
	TEmptyCanvas::~TEmptyCanvas()
	{

	}

	// Inheritance exigences
	void TEmptyCanvas::Init()
	{
	}

	void TEmptyCanvas::Enable()
	{
		gl::framebuffer::enable_depth_test(0);
	}

	void TEmptyCanvas::Disable()
	{
		gl::framebuffer::disable_depth_test(0);
	}
	// END CLASS DECLARATION
}
