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

#ifndef DONUT_PIPELINE_LOADER
#define DONUT_PIPELINE_LOADER

// Library includes
#include "base/common.h"
#include "graphics/shaderdata.h"
#include "recipe/pipelinedescriptor.h"

// External includes
#include <vector>
#include <map>

namespace Donut
{
    // Class that manages the rendering pipelines
    class TPipelineLoader : public Singleton<TPipelineLoader>
    {
        public:
            //Base
            TPipelineLoader();
            ~TPipelineLoader();
            
            // if it is registers it into memory
            void Init();

            // This function searches for a given sugar file and determines either or 
            // not it has been found and returns it if it has.
            const TPipelineDescriptor& FetchPipeline(const std::string& _pipelineName);
        protected:
            // Parses the sugar sub_directory
            void LoadPipelines();

        protected:
            std::string m_pipelineFolder;
            std::map<std::string, TPipelineDescriptor> m_pipelines;
    };
}
#endif // DONUT_PIPELINE_LOADER
 