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

// Library includes
#include "pipelineloader.h"
#include "base/common.h"
#include "tools/fileloader.h"
#include "tools/xmlhelpers.h"

#include "resourcemanager.h"
#include "resource/common.h"
#include "resource/shaderfilehandler.h"
#include "butter/types.h"
#include "butter/stream.h"

// STL includes
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fstream>

namespace Donut
{
    TPipelineLoader::TPipelineLoader()
    {

    }


    TPipelineLoader::~TPipelineLoader()
    {
        
    }

    void TPipelineLoader::Init()
    {
        RESOURCE_WARNING("========= PIPLINE LOADER INIT =========");
        LoadPipelines();
        RESOURCE_WARNING("=====================================");

    }

    void TPipelineLoader::LoadPipelines()
    {   
        const std::string& rootAssetDirectory = ResourceManager::Instance().RootAssetsFolder();
        std::string pipelineFolder(rootAssetDirectory + "/common/pipelines");

        std::vector<std::string> pipelineFiles;
        GetExtensionFileList(pipelineFolder, ".pipeline", pipelineFiles);
        foreach_macro(pipeline, pipelineFiles)
        {
            TPipelineDescriptor newPipeline;
            ParsePipelineFile(*pipeline, newPipeline);
            RESOURCE_INFO("Pipeline "<< newPipeline.name<<" file: "<< *pipeline);
            m_pipelines[newPipeline.name] = newPipeline;
        }
    }
   
    const TPipelineDescriptor& TPipelineLoader::FetchPipeline(const std::string& _pipelineName)
    {
        RESOURCE_DEBUG(_pipelineName<<" is requested");
        auto ite = m_pipelines.find(_pipelineName);
        ASSERT_MSG((ite!=m_pipelines.end()), "Pipeline not found: "<<_pipelineName);
        return ite->second;
    }

}