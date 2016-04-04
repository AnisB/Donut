/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/

#ifndef DONUT_FLOUR_H
#define DONUT_FLOUR_H


// Std includes
#include "core/node.h"
#include "core/camera.h"
#include "graphics/light.h"
#include "graphics/sphericalharmonics.h"
#include "base/macro.h"

// STL includes
#include <vector>

namespace Donut
{
	struct TFlour
	{
		// Consrtuctor
		TFlour(const STRING_TYPE& _fileName)
		: root(nullptr)
		, sh(nullptr)
		, filename(_fileName)
		, pipelineName("minimal")
		{

		}
		//Destructor
		~TFlour()
		{
			if(root)
				delete root;

			foreach_macro(light, lights)
			{
				delete *light;
			}

			if(sh)
				delete sh;
		}

		// Generic data
		STRING_TYPE filename;
		STRING_TYPE pipelineName;
		
		TNode* root;
		std::vector<TLight*> lights;
		TSphericalHarmonics* sh;
	};

	// Flour builder
	TFlour* GenerateFlour(const STRING_TYPE& _flourName);
}

#endif // DONUT_FLOUR_H