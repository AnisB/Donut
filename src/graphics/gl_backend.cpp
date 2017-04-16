
// External includes
#include <GL/glew.h>
#ifndef GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GL3
#endif
#include <GLFW/glfw3.h>

// Library includes
#include "gl_backend.h"
#include "common.h"

namespace Donut
{
	namespace GL
	{
		static void error_callback(int error, const char* description)
		{
			GRAPHICS_ERROR(error << " " << description);
		}


		struct GLRenderEnvironement
		{
			GLFWwindow* window;
		};

		// Builds and returns a default graphics setting for an opengl environement
		TGraphicsSettings default_settings()
		{
			TGraphicsSettings settings;
			settings.backend = RenderingBackEnd::OPENGL;
			settings.data[GLData::ERROR_CALLBACK] = (uint64_t)error_callback;
			settings.data[GLData::MAJOR_VERSION] = 4;
			settings.data[GLData::MINOR_VERSION] = 1;
			settings.width = 1280;
			settings.lenght = 720;
			return settings;
		}

		bool init_render_system()
		{
			return glfwInit();
		}

		void shutdown_render_system()
		{
			glfwTerminate();
		}

		RenderEnvironment create_render_environment(const TGraphicsSettings& graphic_settings)
		{
			// The the error callback
			glfwSetErrorCallback((ErrorCallBack)graphic_settings.data[GLData::ERROR_CALLBACK]);

 			// Setting the context info
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, graphic_settings.data[GLData::MAJOR_VERSION]);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, graphic_settings.data[GLData::MINOR_VERSION]);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			// Window creation
 			GLFWwindow* window_ptr = glfwCreateWindow(graphic_settings.width, graphic_settings.lenght, graphic_settings.window_name.c_str(), graphic_settings.fullScreen? glfwGetPrimaryMonitor():NULL, NULL);
 			if(!window_ptr)
 			{
 				return 0;
 			}

 			// Setting context
			glfwMakeContextCurrent(window_ptr);

		    // Initiating glew
			glewExperimental = GL_TRUE;
			GLenum glewReturn = glewInit();
			if(glewReturn)
			{
				GRAPHICS_ERROR("Error: "<<glewGetErrorString(glewReturn));
			    glfwDestroyWindow(window_ptr);
 				return 0;
			}
			
			const GLubyte* renderer = glGetString (GL_RENDERER); 
			const GLubyte* version = glGetString (GL_VERSION); 
			GRAPHICS_DEBUG("Renderer: "<<renderer);
			GRAPHICS_DEBUG("Version: "<<version);

 			// Setting the rendering flag
   			glfwSetInputMode(window_ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   			// Create the 
 			GLRenderEnvironement* gl_render_env = new GLRenderEnvironement();
 			gl_render_env->window = window_ptr;

			return (RenderEnvironment)gl_render_env;
		}

		void destroy_render_environment(RenderEnvironment render_environment)
		{
			GLRenderEnvironement* gl_re = (GLRenderEnvironement*)render_environment;
			glfwDestroyWindow(gl_re->window);
		}

		RenderWindow render_window(RenderEnvironment render_environement)
		{
			GLRenderEnvironement* gl_re = (GLRenderEnvironement*)render_environement;
			return (RenderWindow) gl_re->window;
		}
	}
}