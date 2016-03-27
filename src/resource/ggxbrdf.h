#ifndef GGX_BRDF_H
#define GGX_BRDF_H

#include "graphics/common.h"

namespace Donut
{
	struct TGGXBRDF
	{
		TGGXBRDF()
		: data(nullptr)
		, m_id(0)
		{

		}

		int dimension[3];
		double* data;
		GLuint m_id;
	};
}


#endif // GGX_BRDF_H