// External includes
#include <GL/glew.h>
#ifndef GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GL3
#endif
#include <GLFW/glfw3.h>

// Library includes
#include "bento_base/security.h"
#include "bento_base/log.h"
#include "gpu_backend/gl_backend.h"
#include "input/helper.h"



namespace donut
{
	namespace gl
	{
		static void error_callback(int error, const char* description)
		{
			bento::default_logger()->log(bento::LogLevel::error, "GRAPHICS", description);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			TInputManager* manager = input_manager();
		    assert(manager != NULL);

		    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		    {
		        glfwSetWindowShouldClose(window, GL_TRUE);
		    }

		    if(action == GLFW_PRESS)
		    {
				manager->KeyPressed((TKeyCode::Type)key);
		    }
		    else if(action == GLFW_RELEASE)
		    {
				manager->KeyReleased((TKeyCode::Type)key);
		    }
		}

	 	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	 	{
			TInputManager* manager = input_manager();
			assert(manager != NULL);

		    if(action == GLFW_PRESS)
		    {
				manager->MousePressed((TMouseCode::Type)button);
		    }
		    else if(action == GLFW_RELEASE)
		    {
				manager->MouseReleased((TMouseCode::Type)button);
		    }
	 	}
	 	
	 	void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	 	{

	 	}

	 	void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
	 	{
			TInputManager* manager = input_manager();
			assert(manager != NULL);

		    int width, height;
		    glfwGetFramebufferSize(window, &width, &height);
		    double ratio = width / (float) height;
		    double x = ratio*(2*xpos/(float)width - 1);
		    double y = 2*-ypos/(float)height + 1;
			manager->MouseMoved(x,y);
	 	}

		struct GLRenderEnvironement
		{
			GLFWwindow* window;
		};

		// Builds and returns a default graphics setting for an opengl environement
		TGraphicSettings default_settings()
		{
			TGraphicSettings settings;
			settings.data[GLData::MAJOR_VERSION] = 4;
			settings.data[GLData::MINOR_VERSION] = 1;
			settings.width = 1280;
			settings.lenght = 720;
			settings.fullscreen = false;
			return settings;
		}

		bool init_render_system()
		{
			return glfwInit() == 0;
		}

		void shutdown_render_system()
		{
			glfwTerminate();
		}

		RenderEnvironment create_render_environment(const TGraphicSettings& graphic_settings)
		{
			// The the error callback
			glfwSetErrorCallback(error_callback);

 			// Setting the context info
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, (int) graphic_settings.data[GLData::MAJOR_VERSION]);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, (int) graphic_settings.data[GLData::MINOR_VERSION]);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			// Window creation
 			GLFWwindow* window_ptr = glfwCreateWindow(graphic_settings.width, graphic_settings.lenght, graphic_settings.window_name.c_str(), graphic_settings.fullscreen? glfwGetPrimaryMonitor():NULL, NULL);
 			if(!window_ptr)
 			{
 				return 0;
 			}

 			// Setting context
			glfwMakeContextCurrent(window_ptr);

			// Set the input functions
			glfwSetKeyCallback(window_ptr, key_callback);
			glfwSetMouseButtonCallback(window_ptr, mouse_button_callback);
			glfwSetScrollCallback(window_ptr, mouse_scroll_callback);
			glfwSetCursorPosCallback(window_ptr, mouse_pos_callback);

		    // Initiating glew
			glewExperimental = GL_TRUE;
			GLenum glewReturn = glewInit();
			if(glewReturn)
			{
				bento::default_logger()->log(bento::LogLevel::error, "GRAPHICS", (const char*)glewGetErrorString(glewReturn));
			    glfwDestroyWindow(window_ptr);
 				return 0;
			}
			
			const GLubyte* renderer = glGetString (GL_RENDERER); 
			const GLubyte* version = glGetString (GL_VERSION); 

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

		void collect_inputs(RenderEnvironment render_environement)
		{
	  		glfwPollEvents();
		}

		float get_time()
		{
			return (float)glfwGetTime();
		}
	}
}