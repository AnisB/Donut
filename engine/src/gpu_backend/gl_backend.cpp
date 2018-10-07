// External includes
#include <GL/glew.h>
#ifndef GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GL3
#endif
#include <GLFW/glfw3.h>

// Bento includes
#include "bento_base/security.h"
#include "bento_base/log.h"
#include "bento_collection/dynamic_string.h"

// Library includes
#include "gpu_backend/gl_backend.h"
#include "resource/resource_manager.h"
#include "resource/shader_source.h"
#include "input/helper.h"
#include "graphics/shader.h"

namespace donut
{
	namespace gl
	{
		void clear_state()
		{
			GLenum e = glGetError();
			return;
		}

		bool check_state()
		{
			GLenum e = glGetError();
			return (e == GL_NO_ERROR);
		}

		uint32_t format_to_gl(texture::TFormat::Type type)
		{
			switch (type)
			{
			case donut::texture::TFormat::RGB:
				return GL_RGB;
			case donut::texture::TFormat::RGBA:
				return GL_RGBA;
			case donut::texture::TFormat::DEPTH:
				return GL_DEPTH_COMPONENT;
			default:
				return GL_RGBA;
			}
		}


		uint32_t datatype_to_gl(texture::TDataType::Type data)
		{
			switch (data)
			{
			case donut::texture::TDataType::UNSIGNED_BYTE:
				return GL_UNSIGNED_BYTE;
			case donut::texture::TDataType::FLOAT:
				return GL_FLOAT;
			case donut::texture::TDataType::DEPTH:
				return GL_DEPTH_COMPONENT;
			default:
				return GL_FLOAT;
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

				TextureObject textureObject = ResourceManager::Instance().request_runtime_texture(_tex.id);

				switch (_tex.type)
				{
				case TTextureNature::COLOR:
				{
#if LINUX | WIN32
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _tex.offset, GL_TEXTURE_2D, (GLuint)textureObject, 0);
#endif

#ifdef MACOSX
					glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT + _tex.offset, _tex.id, 0);
#endif
				}
				break;
				case TTextureNature::DEPTH:
				{
#if LINUX | WIN32
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint)textureObject, 0);
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

			TextureObject create(const TTexture& source)
			{
				uint32_t texture_id;
				GL_API_CHECK();
				glGenTextures(1, &texture_id);
				glBindTexture(GL_TEXTURE_2D, texture_id);
				uint32_t format = format_to_gl((texture::TFormat::Type)source.format);
				uint32_t data_type = datatype_to_gl((texture::TDataType::Type)source.data_type);

				// We set the loading parameters only if the texture stores internal data
				if(source.data.size() != 0)
				{
					glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
					glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
					glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
					glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
				}

				// Create the data
				glTexImage2D(GL_TEXTURE_2D, 0, format, source.width, source.height, 0, format, data_type, source.data.begin());
				GL_API_CHECK();

				// For the moment we only generate mipmaps if input data was given
				if (source.data.size() != 0)
				{
					glGenerateMipmap(GL_TEXTURE_2D);
				}

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
				glObjectLabel(GL_TEXTURE, texture_id, bento::strlen32(debug_name), debug_name);
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
				GL_API_CHECK();
				glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, bento::strlen32(sectionName), sectionName);
				GL_API_CHECK();
			}
			void end_render_section()
			{
				GL_API_CHECK();
				glPopDebugGroup();
				GL_API_CHECK();
			}
		}

		namespace geometry
		{
			struct GLGeometry
			{
				uint32_t vertexArray;
				uint32_t vertexBuffer;
				uint32_t indexBuffer;
				int nbVertices;
				TBox3 os_bb;
			};

			GeometryObject create_vnt(const float* data_array, uint32_t num_verts, const unsigned* _indexArray, uint32_t num_faces)
			{
				// Given that we are rendering using an opengl api we need to reverse the y coord of the meshes
				bento::Vector<float> data_array_gl(*bento::common_allocator(), num_verts * 8);
				memcpy(data_array_gl.begin(), data_array, num_verts * 8 * sizeof(float));
				for (uint32_t vert_idx = 0; vert_idx < num_verts; ++vert_idx)
				{
					data_array_gl[8 * vert_idx + 7] = 1.0f - data_array_gl[8 * vert_idx + 7];
				}

				GL_API_CHECK();
				GLGeometry* newModel = new GLGeometry();
				glGenVertexArrays(1, &newModel->vertexArray);
				glBindVertexArray(newModel->vertexArray);

				glGenBuffers(1, &newModel->vertexBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, newModel->vertexBuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float)*num_verts * 8, data_array_gl.begin(), GL_STATIC_DRAW);

				glGenBuffers(1, &newModel->indexBuffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newModel->indexBuffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*num_faces * 3, _indexArray, GL_STATIC_DRAW);

				{
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);
				}

				{
					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 3));
				}

				{
					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 6));
				}

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
				newModel->nbVertices = num_faces * 3;

				// Build the OS AABB
				for (uint32_t vert_idx = 0; vert_idx < num_verts; ++vert_idx)
				{
					box::include_point(newModel->os_bb, *(const bento::Vector3*)&data_array_gl[8 * vert_idx]);
				}

				GL_API_CHECK();

				return (GeometryObject)newModel;
			}


			void destroy_vnt(GeometryObject object)
			{

			}

			void draw(GeometryObject geometry_object)
			{
				if (geometry_object == 0) return;
				GLGeometry* geometry_obj = (GLGeometry*)geometry_object;
				GL_API_CHECK();
				glBindVertexArray(geometry_obj->vertexArray);
				GL_API_CHECK();
				glCullFace(GL_FRONT_AND_BACK);
				GL_API_CHECK();
				glDrawElements(GL_TRIANGLES, geometry_obj->nbVertices, GL_UNSIGNED_INT, 0);
				GL_API_CHECK();
				glBindVertexArray(0);
				GL_API_CHECK();
			}

			void set_bbox(GeometryObject geometry, const TBox3& outbbox)
			{
				if (geometry == 0) return;
				GLGeometry* geometry_obj = (GLGeometry*)geometry;
				geometry_obj->os_bb = outbbox;
			}

			void bbox(GeometryObject geometry, TBox3& outbbox)
			{
				if (geometry == 0) return;
				GLGeometry* geometry_obj = (GLGeometry*)geometry;
				outbbox = geometry_obj->os_bb;
			}
		}

		namespace shader
		{
			void check_shader(GLuint shader_id)
			{
				// flags
			    GLint result = GL_FALSE;
			    int infoLogLength = 0;

			    // Fetching the compulation results
			    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
			    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &infoLogLength);

			    // Failed?
			    if(infoLogLength > 1)
			    {
			    	// OK lets get the error message
			        char* errorMessage = new char[infoLogLength];
			        glGetShaderInfoLog(shader_id, infoLogLength, NULL, errorMessage);
					bento::default_logger()->log(bento::LogLevel::error, "SHADER_COMPILER", errorMessage);
					assert_fail_msg("Shader compilation failed.");
					delete [] errorMessage;
			    }
			}

			bool check_program(GLuint program_id)
			{
				// flags
			    GLint result = GL_FALSE;
			    int infoLogLength = 0;
			    
			    // Fetching the link result
			    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
			    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &infoLogLength);

			    //Failed?
			    if(infoLogLength > 1)
			    {   
			    	// Ok, lets get the error message
			        char* errorMessage = new char[infoLogLength];
			        glGetProgramInfoLog(program_id, infoLogLength, NULL, errorMessage);
					bento::default_logger()->log(bento::LogLevel::error, "SHADER_COMPILER", errorMessage);
					delete [] errorMessage;
					return false;
			    }
			    return true;
			}

			ShaderPipelineObject create_shader(const TShaderPipelineDescriptor& shader_pipeline)
			{
				// Request all the shaders sources
				TShaderSource vertex_shader_source(*bento::common_allocator());
				if (shader_pipeline.vertex != default_shader)
				{
					ResourceManager::Instance().request_asset<TShaderSource>(shader_pipeline.vertex.c_str(), vertex_shader_source);
				}

				TShaderSource tess_control_shader_source(*bento::common_allocator());
				if (shader_pipeline.tess_control != default_shader)
				{
					ResourceManager::Instance().request_asset<TShaderSource>(shader_pipeline.tess_control.c_str(), tess_control_shader_source);
				}

				TShaderSource tess_eval_shader_source(*bento::common_allocator());
				if (shader_pipeline.tess_eval != default_shader)
				{
					ResourceManager::Instance().request_asset<TShaderSource>(shader_pipeline.tess_eval.c_str(), tess_eval_shader_source);
				}

				TShaderSource geometry_shader_source(*bento::common_allocator());
				if (shader_pipeline.geometry != default_shader)
				{
					ResourceManager::Instance().request_asset<TShaderSource>(shader_pipeline.geometry.c_str(), geometry_shader_source);
				}

				TShaderSource fragment_shader_source(*bento::common_allocator());
				if (shader_pipeline.fragment != default_shader)
				{
					ResourceManager::Instance().request_asset<TShaderSource>(shader_pipeline.fragment.c_str(), fragment_shader_source);
				}

				// Load the shader into memory
				return create_shader_from_source(vertex_shader_source.data.size() > 1 ? vertex_shader_source.data.begin() : nullptr,
					tess_control_shader_source.data.size() > 1 ? tess_control_shader_source.data.begin() : nullptr,
					tess_eval_shader_source.data.size() > 1 ? tess_eval_shader_source.data.begin() : nullptr,
					geometry_shader_source.data.size() > 1 ? geometry_shader_source.data.begin() : nullptr,
					fragment_shader_source.data.size() > 1 ? fragment_shader_source.data.begin() : nullptr);
			}

			ShaderPipelineObject create_shader_from_source(const char* vertex_shader_source, const char* tess_control_shader_source,
													const char* tess_eval_shader_source, const char* geometry_shader_source, 
													const char* fragment_shader_source)
			{
				uint32_t program_id = 0;

				GLuint vertexShader = 0;
				GLuint tessControlShader = 0;
				GLuint tessEvalShader = 0;
				GLuint geometryShader = 0;
				GLuint fragmentShader = 0;

				GL_API_CHECK();
				program_id = glCreateProgram();
				GL_API_CHECK();

				char shaderFlags = 0;
				if(vertex_shader_source != nullptr)
				{
					vertexShader = glCreateShader(GL_VERTEX_SHADER);
					GL_API_CHECK();
					const char * vsFile_ptr = vertex_shader_source;
					glShaderSource(vertexShader, 1, (const char **)&vsFile_ptr, NULL);
					GL_API_CHECK();
					glCompileShader(vertexShader);
					GL_API_CHECK();
					check_shader(vertexShader);
					glAttachShader(program_id, vertexShader);
					GL_API_CHECK();
					shaderFlags &= VERTEX_FLAG;

				}
				if (tess_control_shader_source != nullptr)
				{
					tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
					GL_API_CHECK();
					const char * tcsFile_ptr = tess_control_shader_source;
					glShaderSource(tessControlShader, 1, (const char **)&tcsFile_ptr, NULL);
					GL_API_CHECK();
					glCompileShader(tessControlShader);
					GL_API_CHECK();
					check_shader(tessControlShader);
					glAttachShader(program_id, tessControlShader);
					GL_API_CHECK();
					shaderFlags &= TESS_CONTROL_FLAG;
				}

				if (tess_eval_shader_source != nullptr)
				{
					tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
					GL_API_CHECK();
					const char * tesFile_ptr = tess_eval_shader_source;
					glShaderSource(tessEvalShader, 1, (const char **)&tesFile_ptr, NULL);
					GL_API_CHECK();
					glCompileShader(tessEvalShader);
					GL_API_CHECK();
					check_shader(tessEvalShader);
					glAttachShader(program_id, tessEvalShader);
					GL_API_CHECK();
					shaderFlags &= TESS_EVAL_FLAG;
				}

				if (geometry_shader_source != nullptr)
				{
					geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
					GL_API_CHECK();
					const char * gsFile_ptr = geometry_shader_source;
					glShaderSource(geometryShader, 1, (const char **)&gsFile_ptr, NULL);
					GL_API_CHECK();
					glCompileShader(geometryShader);
					GL_API_CHECK();
					glAttachShader(program_id, geometryShader);
					GL_API_CHECK();
					shaderFlags &= GEOMETRY_FLAG;
				}

				if (fragment_shader_source != nullptr)
				{
					fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
					GL_API_CHECK();
					const char * fsFile_ptr = fragment_shader_source;
					glShaderSource(fragmentShader, 1, (const char **)&fsFile_ptr, NULL);
					GL_API_CHECK();
					glCompileShader(fragmentShader);
					GL_API_CHECK();
					check_shader(fragmentShader);
					glAttachShader(program_id, fragmentShader);
					GL_API_CHECK();
					shaderFlags &= FRAGMENT_FLAG;
				}

				glLinkProgram(program_id);
				GL_API_CHECK();

				if(check_program(program_id))
				{
					// Cleaning up the memory required for compilation
					if(shaderFlags & VERTEX_FLAG)
					{
						glDetachShader(program_id, vertexShader);
						GL_API_CHECK();
						glDeleteShader(vertexShader);
						GL_API_CHECK();
					}
					if(shaderFlags & TESS_CONTROL_FLAG)
					{
						glDetachShader(program_id, tessControlShader);
						GL_API_CHECK();
						glDeleteShader(tessControlShader);
						GL_API_CHECK();
					}
					if(shaderFlags & TESS_EVAL_FLAG)
					{
						glDetachShader(program_id, tessEvalShader);
						GL_API_CHECK();
						glDeleteShader(tessEvalShader);
						GL_API_CHECK();
					}
					if(shaderFlags & GEOMETRY_FLAG)
					{
						glDetachShader(program_id, geometryShader);
						GL_API_CHECK();
						glDeleteShader(geometryShader);
						GL_API_CHECK();
					}
					if(shaderFlags & FRAGMENT_FLAG)
					{
						glDetachShader(program_id, fragmentShader);
						GL_API_CHECK();
						glDeleteShader(fragmentShader);
						GL_API_CHECK();
					}
					return (ShaderPipelineObject)program_id;
				}
				else
				{
					assert_fail_msg("Shader creation failed.");
					GL_API_CHECK();
					return 0;
				}
			}
			
			void destroy_shader(ShaderPipelineObject program)
			{
				GL_API_CHECK();
				glDeleteProgram((GLuint)program);
				GL_API_CHECK();
			}

			void bind_shader(ShaderPipelineObject program)
			{
				GL_API_CHECK();
				glUseProgram((GLuint)program);
				GL_API_CHECK();
			}

			void unbind_shader(ShaderPipelineObject program)
			{
				GL_API_CHECK();
				glUseProgram(0);
				GL_API_CHECK();
			}

			void inject_int(ShaderPipelineObject program, int value, const char* slot)
			{
				GL_API_CHECK();
				GLuint location = glGetUniformLocation((GLuint)program, slot);
				glUniform1i(location, value);
				GL_API_CHECK();
			}

			void inject_float(ShaderPipelineObject program, float value, const char* slot)
			{
				GL_API_CHECK();
				GLuint location = glGetUniformLocation((GLuint)program, slot);
				glUniform1f(location, value);
				GL_API_CHECK();
			}

			void inject_vec3(ShaderPipelineObject program, const bento::Vector3& value, const char* slot)
			{
				GL_API_CHECK();
				GLuint location = glGetUniformLocation((GLuint)program, slot);
				glUniform3f(location, (GLfloat)value.x, (GLfloat)value.y, (GLfloat)value.z);
				GL_API_CHECK();
			}

			void inject_vec4(ShaderPipelineObject program, const bento::Vector4& value, const char* slot)
			{
				GL_API_CHECK();
				GLuint location = glGetUniformLocation((GLuint)program, slot);
				glUniform4f(location, (GLfloat)value.x, (GLfloat)value.y, (GLfloat)value.z, (GLfloat)value.w);
				GL_API_CHECK();
			}

			void inject_mat3(ShaderPipelineObject program, const bento::Matrix3& value, const char* slot)
			{
				GL_API_CHECK();
				GLuint location = glGetUniformLocation((GLuint)program, slot);
				glUniformMatrix3fv(location, 1, true, value.m);
				GL_API_CHECK();
			}

			void inject_mat4(ShaderPipelineObject program, const bento::Matrix4& value, const char* slot)
			{
				GL_API_CHECK();
				GLuint location = glGetUniformLocation((GLuint)program, slot);
				glUniformMatrix4fv(location, 1, true, value.m);
				GL_API_CHECK();
			}

			void inject_array(ShaderPipelineObject program, const float* value_array, uint32_t numValues, const char* slot)
			{
				GL_API_CHECK();
				GLuint loc = glGetUniformLocation((GLuint)program, slot);
				if (loc != UINT32_MAX)
				{
					glUniform1fv(loc, numValues, value_array);
				}
				GL_API_CHECK();
			}

			void bind_texture(TextureObject textureObject, GLuint slot)
			{
				GL_API_CHECK();
				glActiveTexture(GL_TEXTURE0 + slot);
				glBindTexture(GL_TEXTURE_2D, (uint32_t)textureObject);
				GL_API_CHECK();
			}

			void bind_cubemap(CubemapObject cubemapObject, GLuint _spot)
			{
				GL_API_CHECK();
				glActiveTexture(GL_TEXTURE0 + _spot);
				glBindTexture(GL_TEXTURE_CUBE_MAP, (uint32_t)cubemapObject);
				GL_API_CHECK();
			}

			void unbind_texture(GLuint _spot)
			{
				GL_API_CHECK();
				glActiveTexture(GL_TEXTURE0 + _spot);
				glBindTexture(GL_TEXTURE_2D, 0);
				GL_API_CHECK();
			}

			void unbind_cubemap(GLuint _spot)
			{
				GL_API_CHECK();
				glActiveTexture(GL_TEXTURE0 + _spot);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
				GL_API_CHECK();
			}
			
			void inject_texture(ShaderPipelineObject program, TextureObject texture_object, uint32_t offset, const char* slot)
			{
				GL_API_CHECK();
				bind_texture(texture_object, offset);
				GLint texRef = glGetUniformLocation((GLuint)program, slot);
				glUniform1i(texRef, 0 + offset);
				GL_API_CHECK();
			}

			void inject_cubemap(ShaderPipelineObject program, CubemapObject cubemap_object, uint32_t offset, const char* slot)
			{
				GL_API_CHECK();
				bind_cubemap(cubemap_object, offset);
				GLint texRef = glGetUniformLocation((GLuint)program, slot);
				glUniform1i(texRef, 0 + offset);
				GL_API_CHECK();
			}
		}
	}
}