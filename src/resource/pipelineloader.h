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

// External includes
#include <vector>
#include <map>

namespace Donut
{
    namespace TCanvasTag
    {
        enum Type
        {
            UNKNOWN = 0,
            EMPTY = 1,
            EFFECT = 2,
            GBUFFER = 3,
        };
    }

    namespace TVFXTag
    {
        enum Type
        {
            UNKNOWN = 0,
            SIMPLEFX = 1,
            ENVIRONEMENT = 2,
            DEFFERED = 3,
        };
    }

    namespace TPassTag
    {
        enum Type
        {
            GEOMETRY = 0,
            VFX = 1,
            UNKNOWN = -1
        };
    }

    // Descriptor for a rendering pipeline
    struct TPipelineCanvas
    {
        TCanvasTag::Type tag;
        std::string output;
    };

    struct TPipelineVFX
    {
        TVFXTag::Type tag;
        std::vector<TTextureInfo> textures;
        TShader shader;
    };

    struct TPipelinePass
    {
        TPassTag::Type tag;
        TPipelineCanvas  canvas;
        TPipelineVFX  vfx;
    };

    struct TPipelineDescriptor
    {
        std::vector<TPipelinePass> passes;
        std::string name;
    };
    
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
            // Parses pipeline file
            void ParsePipelineFile(const std::string& _pipelineFileName, TPipelineDescriptor& _pipeline);

        protected:
            std::string m_pipelineFolder;
            std::map<std::string, TPipelineDescriptor> m_pipelines;
    };
}
#endif // DONUT_PIPELINE_LOADER
 