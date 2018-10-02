#pragma once

// Bento includes
#include <bento_base/security.h>

// Internal includes
#include "graphics/shader.h"
#include "graphics/shaderdata.h"
#include "gpu_backend/gpu_backend.h"
#include "resource/texture.h"
#include "resource/skybox.h"
#include "core/box3.h"

namespace donut {
namespace gl {

	// Generic purpose functions
	void clear_state();
	bool check_state();

	// Geometry API
	namespace geometry
	{
		// The possible function to create a geometry
		GeometryObject create_vnt(const float* _dataArray, int _numVert, const unsigned* _indexArray, int num_faces);
		void destroy_vnt(GeometryObject object);

		// Function to draw a given geometry
		void draw(GeometryObject geometry_object);

		// Functions to handle the bounding box
		void set_bbox(GeometryObject geometry, const TBox3& outbbox);
		void bbox(GeometryObject geometry, TBox3& outbbox);
	}

	#if 0
		#define GL_API_CHECK() {assert_msg(gl::check_state(), FUNCTION_NAME);}
	#else
		#define GL_API_CHECK() {}
	#endif
}
}