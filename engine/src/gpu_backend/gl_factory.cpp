// External includes
#include <GL/glew.h>
#ifndef GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GL3
#endif

// Internal includes
#include "bento_base/log.h"
#include "gpu_backend/gl_factory.h"

// External inclues
#include <GLFW/glfw3.h>


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
}
}
