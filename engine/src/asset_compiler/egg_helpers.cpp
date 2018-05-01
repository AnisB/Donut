// Bento includes
#include <bento_base/security.h>
#include <bento_base/log.h>

// Library include
#include "asset_compiler/egg_helpers.h"
#include "base/stringhelper.h"
#include "resource/egg.h"

// Bento includes
#include <bento_math/types.h>
#include <bento_math/vector3.h>

// External includes
#include <vector>
#include <fstream>

// External includes
#include "tools/tiny_obj_loader.h"

namespace donut
{
	bool read_wavefront(const char *geo_filename, const char* mtl_dir, std::vector<tinyobj::shape_t>& shapes, std::vector<tinyobj::material_t>& materials, tinyobj::attrib_t& attrib)
	{
		// Parse the wafront file
		std::string err;
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, geo_filename, mtl_dir, true);

		if (!err.empty())
			bento::default_logger()->log(bento::LogLevel::error, "WAVEFRONT", err.c_str());
		return ret;
	}

	bool read_egg(const char* target_path, TEgg& output_egg)
	{
		// Read/Parse the wavefront file
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		tinyobj::attrib_t attrib;
		bool res = read_wavefront(target_path, nullptr, shapes, materials, attrib);

		// Quit if there was an error in the parsing of the file
		if (!res) return false;

		// Loop through the shapes
		size_t num_shapes = shapes.size();
		for (size_t shape_idx = 0; shape_idx < num_shapes; shape_idx++)
		{
			tinyobj::shape_t& current_shape = shapes[shape_idx];
			size_t num_faces = current_shape.mesh.num_face_vertices.size();
			size_t index_offset = 0;
			for (size_t face_idx = 0; face_idx < num_faces; face_idx++)
			{
				// The size of the polygon
				int polygon_degree = current_shape.mesh.num_face_vertices[face_idx];
				assert(polygon_degree == 3);

				// Fetch the triangle's indexes
				tinyobj::index_t idxi[3];
				idxi[0] = current_shape.mesh.indices[index_offset + 0];
				idxi[1] = current_shape.mesh.indices[index_offset + 1];
				idxi[2] = current_shape.mesh.indices[index_offset + 2];

				// Push the face indexes
				output_egg._indexes.push_back({ (uint32_t)(index_offset + 0), (uint32_t)(index_offset + 1), (uint32_t)(index_offset + 2) });

				// Grab the vertices
				bento::Vector3 pi[3];
				pi[0] = { attrib.vertices[3 * idxi[0].vertex_index + 0], attrib.vertices[3 * idxi[0].vertex_index + 1] ,attrib.vertices[3 * idxi[0].vertex_index + 2] };
				pi[1] = { attrib.vertices[3 * idxi[1].vertex_index + 0], attrib.vertices[3 * idxi[1].vertex_index + 1] ,attrib.vertices[3 * idxi[1].vertex_index + 2] };
				pi[2] = { attrib.vertices[3 * idxi[2].vertex_index + 0], attrib.vertices[3 * idxi[2].vertex_index + 1] ,attrib.vertices[3 * idxi[2].vertex_index + 2] };

				// Compute the geometric normal
				const bento::Vector3& geometric_normal = bento::normalize(bento::cross(pi[1] - pi[0], pi[2] - pi[0]));

				// Push the vertex normal data
				for (int i = 0; i < 3; ++i)
				{
					// Push vertices
					output_egg._vert_normal_uvs.push_back(pi[i].x);
					output_egg._vert_normal_uvs.push_back(pi[i].y);
					output_egg._vert_normal_uvs.push_back(pi[i].z);

					// Push the normals if any otherwise use the geometric one
					if (!attrib.normals.empty())
					{
						output_egg._vert_normal_uvs.push_back(attrib.normals[3 * idxi[i].normal_index + 0]);
						output_egg._vert_normal_uvs.push_back(attrib.normals[3 * idxi[i].normal_index + 1]);
						output_egg._vert_normal_uvs.push_back(attrib.normals[3 * idxi[i].normal_index + 2]);
					}
					else
					{
						output_egg._vert_normal_uvs.push_back(geometric_normal.x);
						output_egg._vert_normal_uvs.push_back(geometric_normal.y);
						output_egg._vert_normal_uvs.push_back(geometric_normal.z);
					}

					// Push the texcorrds if any, otherwise use 0.0f
					if (!attrib.texcoords.empty())
					{
						output_egg._vert_normal_uvs.push_back(attrib.texcoords[2 * idxi[i].texcoord_index + 0]);
						output_egg._vert_normal_uvs.push_back(attrib.texcoords[2 * idxi[i].texcoord_index + 1]);
					}
					else
					{
						output_egg._vert_normal_uvs.push_back(0.0f);
						output_egg._vert_normal_uvs.push_back(0.0f);
					}
				}


				// Move to the next polygon
				index_offset += polygon_degree;
			}
		}

		return true;
	}
}