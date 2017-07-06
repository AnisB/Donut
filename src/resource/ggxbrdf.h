#ifndef GGX_BRDF_H
#define GGX_BRDF_H

#include "graphics/common.h"

namespace donut
{
	struct TGGXBRDF
	{
		TGGXBRDF()
		: data(nullptr)
		, id(0)
		{

		}

		int dimension[3];
		float* data;
		GLuint id;
	};
}


#endif // GGX_BRDF_H