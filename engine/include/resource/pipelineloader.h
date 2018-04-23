#pragma once

// Library includes
#include "base/Singleton.h"
#include "graphics/shaderdata.h"
#include "recipe/pipelinedescriptor.h"

// External includes
#include <vector>
#include <map>

namespace donut
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
            const TPipelineDescriptor& FetchPipeline(const STRING_TYPE& _pipelineName);
        protected:
            // Parses the sugar sub_directory
            void LoadPipelines();

        protected:
            STRING_TYPE m_pipelineFolder;
            std::map<STRING_TYPE, TPipelineDescriptor> m_pipelines;
    };
}