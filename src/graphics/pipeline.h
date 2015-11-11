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

// Library includes
#include "graphics/pass.h"
#include "graphics/light.h"
#include "core/node.h"

namespace Donut
{
	enum TPipelineTAG
	{
		SIMPLE = 0x0000,
		DEFFERED =  0x0001,
		DEPTH_OF_FIELD =  0x0002,
		SCREN_SPACE_AMBIENT_OCCLUSION =  0x0004,
	};

	struct TPipeline
	{
		TPipeline();
		~TPipeline();
		void BuildPipelineData();
		Camera* camera;
		std::vector<TPass*> passes;
		TBufferOutput pipelineData;
	};

	TPipeline* GenerateGraphicPipeline(TNode* _rootNode, std::vector<TLight*> _lights, int _width, int _height, int _pipelineTAGS);
}

#endif // GRAPHIC_PIPELINE_FACTORY_DONUT
