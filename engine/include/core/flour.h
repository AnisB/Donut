#pragma once


// Std includes
#include "core/node.h"
#include "core/camera.h"
#include "graphics/light.h"
#include "graphics/sphericalharmonics.h"
#include "resource/types.h"
#include "resource/texture.h"
#include "resource/skybox.h"

// STL includes
#include <vector>

namespace donut
{
	// Foward declare
	class TMesh;
	
	struct TFlour
	{
		// Consrtuctor
		TFlour(bento::IAllocator& alloc)
		: sh(nullptr)
		, pipelineName("minimal")
		, skybox(UINT32_MAX)
		, nodes(alloc)
		{

		}
		//Destructor
		~TFlour()
		{
			if(sh)
				delete sh;
		}

		// Generic data
		std::string pipelineName;
		
		bento::Vector<TNode> nodes;
		std::vector<TLight> lights;
		TSphericalHarmonics* sh;
		CUBEMAP_GUID skybox;
	};

	// Flour builder
	TFlour* GenerateFlour(const char* flour_name);
}