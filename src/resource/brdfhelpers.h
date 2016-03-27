#ifndef BRDF_HELPERS
#define BRDF_HELPERS


// Library includes
#include "ggxbrdf.h"
#include "graphics/common.h"
#include "common.h"

namespace Donut
{
	namespace BRDFHelpers
	{
		TGGXBRDF* LoadBRDF(const std::string& _name);
		void CreateBRDF(TGGXBRDF* _brdf);
	}
}

#endif // BRDF_HELPERS