// External includes
#include <GL/glew.h>
#ifndef GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GL3
#endif
#include <GLFW/glfw3.h>

// Internal includes
#include "bento_base/log.h"
#include "gpu_backend/gl_factory.h"

namespace donut {
namespace gl {

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

	namespace window
	{
		void show(RenderWindow window)
		{
			GLFWwindow* window_ptr = (GLFWwindow*) window;
 			glfwShowWindow(window_ptr);
		}

		void hide(RenderWindow window)
		{
			GLFWwindow* window_ptr = (GLFWwindow*) window;
 			glfwHideWindow(window_ptr);
		}

		bool is_active(RenderWindow window)
		{
			GLFWwindow* window_ptr = (GLFWwindow*) window;
			return !glfwWindowShouldClose(window_ptr);
		}

		void swap(RenderWindow window)
		{
			GLFWwindow* window_ptr = (GLFWwindow*) window;
	  		glfwSwapBuffers (window_ptr);
		}
	}

	namespace framebuffer
	{
		uint32_t create()
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

		void destroy(uint32_t _frameBuffer)
		{
			GL_API_CHECK();
#if LINUX | WIN32
			glDeleteFramebuffers(1, &_frameBuffer);
#endif
#ifdef MACOSX
			glDeleteFramebuffersEXT(1, &_frameBuffer);
#endif
			GL_API_CHECK();
		}

		bool check()
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

		void bind(uint32_t frame_buffer)
		{
			GL_API_CHECK();
#if LINUX | WIN32
			glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
#endif
#ifdef MACOSX
			glBindFramebufferEXT(GL_FRAMEBUFFER, frame_buffer);
#endif
			GL_API_CHECK();
		}

		void unbind()
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

		void clear(uint32_t frame_buffer)
		{
			GL_API_CHECK();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			GL_API_CHECK();
		}

		void set_clear_color(uint32_t frame_buffer, const bento::Vector4& color)
		{
			GL_API_CHECK();
			glClearColor(color.x, color.y, color.z, color.w);
			GL_API_CHECK();
		}

		void bind_texture(const TTextureInfo& _tex)
		{
			GL_API_CHECK();

			switch (_tex.type)
			{
			case TTextureNature::COLOR:
			{
	#if LINUX | WIN32
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _tex.offset, GL_TEXTURE_2D, _tex.texID, 0);
	#endif

	#ifdef MACOSX
				glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT + _tex.offset, _tex.texID, 0);
	#endif
			}
			break;
			case TTextureNature::DEPTH:
			{
	#if LINUX | WIN32
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _tex.texID, 0);
	#endif

	#ifdef MACOSX
				glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _tex.texID, 0);
	#endif
			}
			break;
			default:
				bento::default_logger()->log(bento::LogLevel::error, "GRAPHICS_TEXTURE", "Unsupported texture type");
			}
			GL_API_CHECK();
		}

		void set_num_render_targets(uint8_t num_render_targets)
		{
			switch(num_render_targets)
			{
				case 1:
				{
					GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT};
	    			glDrawBuffers(1, buffers);
				}
				break;
				case 2:
				{
					GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT};
	    			glDrawBuffers(2, buffers);
				}
				break;
				case 3:
				{
					GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT};
	    			glDrawBuffers(3, buffers);
				}
				break;
				case 4:
				{
					GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT};
	    			glDrawBuffers(4, buffers);
				}
				break;
			}
		}

		void enable_depth_test(uint32_t frame_buffer)
		{
			glEnable(GL_DEPTH_TEST);
		}

		void disable_depth_test(uint32_t frame_buffer)
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	namespace texture2D
	{
		void create(TTextureInfo& _tex, int width, int height)
		{
			GL_API_CHECK();
			glGenTextures(1, &_tex.texID);
			glBindTexture(GL_TEXTURE_2D, _tex.texID);
			if (_tex.type == TTextureNature::COLOR)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, 0);
			}
			else if (_tex.type == TTextureNature::DEPTH)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glBindTexture(GL_TEXTURE_2D, 0);
			GL_API_CHECK();
		}

		void destroy(TTextureInfo& _tex)
		{
			GL_API_CHECK();
#if LINUX | WIN32
			glDeleteTextures(1, &_tex.texID);
#endif
#ifdef MACOSX
			glDeleteTexturesEXT(1, &_tex.texID);
#endif
			GL_API_CHECK();
		}

		void create(TTexture& source)
		{
			GL_API_CHECK();
			glGenTextures(1, &source.FID);
			glBindTexture(GL_TEXTURE_2D, source.FID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, source.FWidth, source.FHeight, 0, GL_RGBA, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, source.FFormat, source.FWidth, source.FHeight, 0, source.FFormat, GL_UNSIGNED_BYTE, source.FData);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glBindTexture(GL_TEXTURE_2D, 0);
			GL_API_CHECK();
		}

		void destroy(TTexture& tex)
		{
			GL_API_CHECK();
#if LINUX | WIN32
			glDeleteTextures(1, &tex.FID);
#endif
#ifdef MACOSX
			glDeleteTexturesEXT(1, &tex.FID);
#endif
			GL_API_CHECK();
		}

	}

	namespace textureCUBE
	{
		void create(TSkyboxTexture& target_texture)
		{
			GL_API_CHECK();
			glGenTextures(1, &target_texture.id);
			glBindTexture(GL_TEXTURE_CUBE_MAP, target_texture.id);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, target_texture.textures[0]->FFormat, target_texture.textures[0]->FWidth, target_texture.textures[0]->FHeight, 0, target_texture.textures[0]->FFormat, GL_UNSIGNED_BYTE, target_texture.textures[0]->FData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, target_texture.textures[1]->FFormat, target_texture.textures[1]->FWidth, target_texture.textures[1]->FHeight, 0, target_texture.textures[1]->FFormat, GL_UNSIGNED_BYTE, target_texture.textures[1]->FData);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, target_texture.textures[2]->FFormat, target_texture.textures[2]->FWidth, target_texture.textures[2]->FHeight, 0, target_texture.textures[2]->FFormat, GL_UNSIGNED_BYTE, target_texture.textures[2]->FData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, target_texture.textures[3]->FFormat, target_texture.textures[3]->FWidth, target_texture.textures[3]->FHeight, 0, target_texture.textures[3]->FFormat, GL_UNSIGNED_BYTE, target_texture.textures[3]->FData);
			
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, target_texture.textures[4]->FFormat, target_texture.textures[4]->FWidth, target_texture.textures[4]->FHeight, 0, target_texture.textures[4]->FFormat, GL_UNSIGNED_BYTE, target_texture.textures[4]->FData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, target_texture.textures[5]->FFormat, target_texture.textures[5]->FWidth, target_texture.textures[5]->FHeight, 0, target_texture.textures[5]->FFormat, GL_UNSIGNED_BYTE, target_texture.textures[5]->FData);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			GL_API_CHECK();
		}

		void destroy(TSkyboxTexture& target_texture)
		{
			GL_API_CHECK();
#if LINUX | WIN32
			glDeleteTextures(1, &target_texture.id);
#endif
#ifdef MACOSX
			glDeleteTexturesEXT(1, &target_texture.id);
#endif
			GL_API_CHECK();
		}
	}

	void ReadRGBFrameBuffer(int _width, int _length, unsigned char* _output)
	{
		GL_API_CHECK();
		glReadPixels(0, 0, _width, _length, GL_RGB, GL_UNSIGNED_BYTE, _output);
		GL_API_CHECK();
	}

	namespace geometry
	{
		struct TGeometry
		{
			uint32_t vertexArray;
			uint32_t vertexBuffer;
			uint32_t indexBuffer;
		    int nbVertices;
			TBox3 os_bb;
		};

		GeometryObject create_vnt(float* _dataArray, int _numVert, unsigned* _indexArray, int num_faces)
		{
			GL_API_CHECK();
			TGeometry* newModel = new TGeometry();
			glGenVertexArrays(1, &newModel->vertexArray);
			glBindVertexArray(newModel->vertexArray);

			glGenBuffers(1, &newModel->vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, newModel->vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*_numVert * 8, _dataArray, GL_STATIC_DRAW);

			glGenBuffers(1, &newModel->indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newModel->indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*num_faces * 3, _indexArray, GL_STATIC_DRAW);

			{
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			}

			{
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*_numVert * 3));
			}

			{
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*_numVert * 6));
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			newModel->nbVertices = num_faces * 3;

			// Build the OS AABB
			newModel->os_bb.IncludePoints(_dataArray, _numVert);

			GL_API_CHECK();

			return (GeometryObject)newModel;
		}


		void destroy_vnt(GeometryObject object)
		{

		}

		void draw(GeometryObject geometry_object)
		{
			if (geometry_object == 0) return;
			TGeometry* geometry_obj = (TGeometry*)geometry_object;
			glBindVertexArray(geometry_obj->vertexArray);
			glDrawElements(GL_TRIANGLES, geometry_obj->nbVertices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		void set_bbox(GeometryObject geometry, const TBox3& outbbox)
		{
			if (geometry == 0) return;
			TGeometry* geometry_obj = (TGeometry*)geometry;
			geometry_obj->os_bb = outbbox;
		}

		void bbox(GeometryObject geometry, TBox3& outbbox)
		{
			if (geometry == 0) return;
			TGeometry* geometry_obj = (TGeometry*)geometry;
			outbbox = geometry_obj->os_bb;
		}
	}
}
}
