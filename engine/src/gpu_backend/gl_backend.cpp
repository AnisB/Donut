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
#include "gpu_backend/gl_factory.h"
#include "input/helper.h"

namespace donut
{
	namespace gl
	{
		uint32_t format_to_gl(texture::TFormat::Type type)
		{
			switch (type)
			{
			case donut::texture::TFormat::RGB:
				return GL_RGB;
			case donut::texture::TFormat::RGBA:
				return GL_RGBA;
			default:
				return GL_RGBA;
			}
		}

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
			settings.backend = RenderingBackEnd::OPENGL;
			settings.fullscreen = false;
			return settings;
		}

		namespace render_system
		{
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
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, (int)graphic_settings.data[GLData::MAJOR_VERSION]);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, (int)graphic_settings.data[GLData::MINOR_VERSION]);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

				// Window creation
				GLFWwindow* window_ptr = glfwCreateWindow(graphic_settings.width, graphic_settings.lenght, graphic_settings.window_name.c_str(), graphic_settings.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
				if (!window_ptr)
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
				if (glewReturn)
				{
					bento::default_logger()->log(bento::LogLevel::error, "GRAPHICS", (const char*)glewGetErrorString(glewReturn));
					glfwDestroyWindow(window_ptr);
					return 0;
				}

				const GLubyte* renderer = glGetString(GL_RENDERER);
				const GLubyte* version = glGetString(GL_VERSION);

				// Setting the rendering flag
				glfwSetInputMode(window_ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				// Create the 
				GLRenderEnvironement* gl_render_env = new GLRenderEnvironement();
				gl_render_env->window = window_ptr;

				// Clear the error state
				gl::clear_state();

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
				return (RenderWindow)gl_re->window;
			}

			void collect_inputs(RenderEnvironment render_environement)
			{
				glfwPollEvents();
			}

			float get_time(RenderEnvironment render_environement)
			{
				return (float)glfwGetTime();
			}
		}

		namespace window
		{
			void show(RenderWindow window)
			{
				GLFWwindow* window_ptr = (GLFWwindow*)window;
				glfwShowWindow(window_ptr);
			}

			void hide(RenderWindow window)
			{
				GLFWwindow* window_ptr = (GLFWwindow*)window;
				glfwHideWindow(window_ptr);
			}

			bool is_active(RenderWindow window)
			{
				GLFWwindow* window_ptr = (GLFWwindow*)window;
				return !glfwWindowShouldClose(window_ptr);
			}

			void swap(RenderWindow window)
			{
				GLFWwindow* window_ptr = (GLFWwindow*)window;
				glfwSwapBuffers(window_ptr);
			}
		}

		namespace framebuffer
		{
			FramebufferObject create()
			{
				GL_API_CHECK();
				GLuint frameBufferIndex;
#if LINUX | WIN32
				glGenFramebuffers(1, &frameBufferIndex);
#endif
#ifdef MACOSX 
				glGenFramebuffersEXT(1, &frameBufferIndex);
#endif
				GL_API_CHECK();
				return frameBufferIndex;
			}

			void destroy(FramebufferObject frame_buffer)
			{
				GL_API_CHECK();
				uint32_t framebuffer_idx = (uint32_t)frame_buffer;
#if LINUX | WIN32
				glDeleteFramebuffers(1, &framebuffer_idx);
#endif
#ifdef MACOSX
				glDeleteFramebuffersEXT(1, &framebuffer_idx);
#endif
				GL_API_CHECK();
			}

			bool check(FramebufferObject frame_buffer)
			{
				GL_API_CHECK();
				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				{
					bento::default_logger()->log(bento::LogLevel::error, "GRAPHICS_FRAMEBUFFER", "Framebuffer check");
					return false;
				}
				GL_API_CHECK();
				return true;
			}

			void bind(FramebufferObject frame_buffer)
			{
				GL_API_CHECK();
#if LINUX | WIN32
				glBindFramebuffer(GL_FRAMEBUFFER, (uint32_t)frame_buffer);
#endif
#ifdef MACOSX
				glBindFramebufferEXT(GL_FRAMEBUFFER, frame_buffer);
#endif
				GL_API_CHECK();
			}

			void unbind(FramebufferObject frame_buffer)
			{
				GL_API_CHECK();
#if LINUX | WIN32
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif

#ifdef MACOSX
				glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
#endif
				GL_API_CHECK();
			}

			void clear(FramebufferObject frame_buffer)
			{
				GL_API_CHECK();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				GL_API_CHECK();
			}

			void set_clear_color(FramebufferObject frame_buffer, const bento::Vector4& color)
			{
				GL_API_CHECK();
				glClearColor(color.x, color.y, color.z, color.w);
				GL_API_CHECK();
			}

			void bind_texture(FramebufferObject frame_buffer, const TTextureInfo& _tex)
			{
				GL_API_CHECK();

				switch (_tex.type)
				{
				case TTextureNature::COLOR:
				{
#if LINUX | WIN32
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _tex.offset, GL_TEXTURE_2D, (GLuint)_tex.id, 0);
#endif

#ifdef MACOSX
					glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT + _tex.offset, _tex.id, 0);
#endif
				}
				break;
				case TTextureNature::DEPTH:
				{
#if LINUX | WIN32
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint)_tex.id, 0);
#endif

#ifdef MACOSX
					glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _tex.id, 0);
#endif
				}
				break;
				default:
					bento::default_logger()->log(bento::LogLevel::error, "GRAPHICS_TEXTURE", "Unsupported texture type");
				}
				GL_API_CHECK();
			}

			void set_num_render_targets(FramebufferObject frame_buffer, uint8_t num_render_targets)
			{
				switch (num_render_targets)
				{
				case 1:
				{
					GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT };
					GL_API_CHECK();
					glDrawBuffers(1, buffers);
					GL_API_CHECK();
				}
				break;
				case 2:
				{
					GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
					GL_API_CHECK();
					glDrawBuffers(2, buffers);
					GL_API_CHECK();
				}
				break;
				case 3:
				{
					GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT };
					GL_API_CHECK();
					glDrawBuffers(3, buffers);
					GL_API_CHECK();
				}
				break;
				case 4:
				{
					GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT };
					GL_API_CHECK();
					glDrawBuffers(4, buffers);
					GL_API_CHECK();
				}
				break;
				}
			}

			void enable_depth_test(FramebufferObject frame_buffer)
			{
				GL_API_CHECK();
				glEnable(GL_DEPTH_TEST);
				GL_API_CHECK();
			}

			void disable_depth_test(FramebufferObject frame_buffer)
			{
				GL_API_CHECK();
				glDisable(GL_DEPTH_TEST);
				GL_API_CHECK();
			}
		}

		namespace texture2D
		{
			TextureObject create(TTextureNature::Type nature, int width, int height)
			{
				uint32_t texture_id;
				GL_API_CHECK();
				glGenTextures(1, &texture_id);
				glBindTexture(GL_TEXTURE_2D, texture_id);
				switch (nature)
				{
				case TTextureNature::COLOR:
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, 0);
				}
				break;
				case TTextureNature::DEPTH:
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
				}
				break;
				};
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				glBindTexture(GL_TEXTURE_2D, 0);

				GL_API_CHECK();
				return (TextureObject)texture_id;
			}

			TextureObject create_color_texture(const TTexture& source)
			{
				uint32_t texture_id;
				GL_API_CHECK();
				glGenTextures(1, &texture_id);
				glBindTexture(GL_TEXTURE_2D, texture_id);
				uint32_t format = format_to_gl((texture::TFormat::Type)source.format);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
				glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
				glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
				glTexImage2D(GL_TEXTURE_2D, 0, format, source.width, source.height, 0, format, GL_UNSIGNED_BYTE, source.data.begin());
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glBindTexture(GL_TEXTURE_2D, 0);
				GL_API_CHECK();
				return (TextureObject)texture_id;
			}

			void destroy(TextureObject tex)
			{
				uint32_t texture_id = (uint32_t)tex;
				GL_API_CHECK();
	#if LINUX | WIN32
				glDeleteTextures(1, &texture_id);
	#endif
	#ifdef MACOSX
				glDeleteTexturesEXT(1, &texture_id);
	#endif
				GL_API_CHECK();
			}

			void set_debug_name(TextureObject texture, const char* debug_name)
			{
				uint32_t texture_id = (uint32_t)texture;
				glObjectLabel(GL_TEXTURE, texture_id, strlen(debug_name), debug_name);
			}
		}

		namespace textureCUBE
		{
			CubemapObject create(const TSkybox& source_skybox)
			{
				uint32_t cubemap_id;
				GL_API_CHECK();
				glGenTextures(1, &cubemap_id);
				GL_API_CHECK();
				glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
				GL_API_CHECK();
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				GL_API_CHECK();
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				GL_API_CHECK();
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				GL_API_CHECK();
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				GL_API_CHECK();
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				GL_API_CHECK();
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
				GL_API_CHECK();
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);
				GL_API_CHECK();
				uint32_t format = format_to_gl((texture::TFormat::Type)source_skybox.format);
				uint32_t resolution = source_skybox.width;
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, resolution, resolution, 0, format, GL_UNSIGNED_BYTE, source_skybox.faces[0].begin());
				GL_API_CHECK();
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, resolution, resolution, 0, format, GL_UNSIGNED_BYTE, source_skybox.faces[1].begin());
				GL_API_CHECK();
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, resolution, resolution, 0, format, GL_UNSIGNED_BYTE, source_skybox.faces[2].begin());
				GL_API_CHECK();
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, resolution, resolution, 0, format, GL_UNSIGNED_BYTE, source_skybox.faces[3].begin());
				GL_API_CHECK();
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, resolution, resolution, 0, format, GL_UNSIGNED_BYTE, source_skybox.faces[4].begin());
				GL_API_CHECK();
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, resolution, resolution, 0, format, GL_UNSIGNED_BYTE, source_skybox.faces[5].begin());
				GL_API_CHECK();
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
				GL_API_CHECK();
				return (CubemapObject)cubemap_id;
			}

			void destroy(CubemapObject cubemap)
			{
				uint32_t cubemap_id = (uint32_t)cubemap;
				GL_API_CHECK();
#if LINUX | WIN32
				glDeleteTextures(1, &cubemap_id);
#endif
#ifdef MACOSX
				glDeleteTexturesEXT(1, &cubemap_id);
#endif
				GL_API_CHECK();
			}
		}

		namespace render_section
		{
			void start_render_section(const char* sectionName)
			{
				glPushDebugGroup(0, 0, strlen(sectionName), sectionName);
			}
			void end_render_section()
			{
				glPopDebugGroup();
			}
		}
	}
}