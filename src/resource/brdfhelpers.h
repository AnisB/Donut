#ifndef BRDF_HELPERS
#define BRDF_HELPERS


// Library includes
#include "ggxbrdf.h"
#include "graphics/common.h"
#include "common.h"

namespace donut
{
	namespace BRDFHelpers
	{
		TGGXBRDF* LoadBRDF(const STRING_TYPE& _name);
		void CreateBRDF(TGGXBRDF* _brdf);
	}
}

#endif // BRDF_HELPERS