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


#ifndef GRAPHIC_PIPELINE_FACTORY_DONUT
#define GRAPHIC_PIPELINE_FACTORY_DONUT

// Donut includes
#include "pass.h"
#include "light.h"
#include "core/node.h"
#include "core/flour.h"

namespace Donut
{
	struct TPipeline
	{
		// Init and destruction
		TPipeline();
		~TPipeline();

		// This function build the structure of shader data between the 
		// different renderpasses
		void BuildPipelineData();

		// Attributes
		Camera* camera;
		std::vector<TPass*> passes;
		TBufferOutput pipelineData;
	};

	// Pipeline builder
	TPipeline* GenerateGraphicPipeline(TFlour* _scene, int _width, int _height);
}

#endif // GRAPHIC_PIPELINE_FACTORY_DONUT
