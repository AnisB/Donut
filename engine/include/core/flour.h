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
		TFlour(const STRING_TYPE& _fileName)
		: root(nullptr)
		, sh(nullptr)
		, filename(_fileName)
		, pipelineName("minimal")
		, skybox(UINT32_MAX)
		{

		}
		//Destructor
		~TFlour()
		{
			if(root)
				delete root;

			if(sh)
				delete sh;
		}

		// Generic data
		STRING_TYPE filename;
		STRING_TYPE pipelineName;
		
		TNode* root;
		std::vector<TLight> lights;
		TSphericalHarmonics* sh;
		CUBEMAP_GUID skybox;
	};

	// Flour builder
	TFlour* GenerateFlour(const STRING_TYPE& _flourName);
}