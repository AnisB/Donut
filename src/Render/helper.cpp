#include "helper.h"


void CheckGLState(const std::string& desc)
{
	if(desc=="FLUSH")
		return;
	GLenum e = glGetError();
	if (e != GL_NO_ERROR) 
	{
		RENDER_ERR("OpenGL error in: "<<desc.c_str()<<" "<<gluErrorString(e)<<" "<<e);
	}
	else
	{
		RENDER_DEBUG("No OpenGL errors@"<<desc);
	}
}