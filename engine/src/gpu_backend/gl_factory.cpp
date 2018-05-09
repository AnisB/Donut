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
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _tex.offset, GL_TEXTURE_2D, _tex.id, 0);
	#endif

	#ifdef MACOSX
				glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT + _tex.offset, _tex.id, 0);
	#endif
			}
			break;
			case TTextureNature::DEPTH:
			{
	#if LINUX | WIN32
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _tex.id, 0);
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
			uint32_t texture_id = tex;
			GL_API_CHECK();
#if LINUX | WIN32
			glDeleteTextures(1, &texture_id);
#endif
#ifdef MACOSX
			glDeleteTexturesEXT(1, &texture_id);
#endif
			GL_API_CHECK();
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
			uint32_t cubemap_id = cubemap;
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

		GeometryObject create_vnt(const float* data_array, int num_verts, const unsigned* _indexArray, int num_faces)
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
			glBindVertexArray(geometry_obj->vertexArray);
			glDrawElements(GL_TRIANGLES, geometry_obj->nbVertices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
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
}
}
