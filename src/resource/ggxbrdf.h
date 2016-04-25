#ifndef GGX_BRDF_H
#define GGX_BRDF_H

#include "graphics/common.h"

namespace Donut
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