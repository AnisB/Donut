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

// Bento includes
#include <bento_base/security.h>

// Library includes
#include "resource/pipelineloader.h"
#include "tools/fileloader.h"
#include "tools/xmlhelpers.h"

#include "resource/resourcemanager.h"
#include "resource/common.h"
#include "resource/shaderfilehandler.h"

// Bento includes
#include <bento_math/types.h>

namespace donut
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
        const STRING_TYPE& root_asset_dir = ResourceManager::Instance().RootAssetsFolder();

        std::vector<STRING_TYPE> pipelineFiles;
		get_all_files_with_extension(root_asset_dir.c_str(), ".pipeline", pipelineFiles);
        for(auto& pipeline : pipelineFiles)
        {
            TPipelineDescriptor newPipeline;
            ParsePipelineFile(pipeline, newPipeline);
            RESOURCE_INFO("Pipeline "<< newPipeline.name<<" file: "<< pipeline);
            m_pipelines[newPipeline.name] = newPipeline;
        }
    }
   
    const TPipelineDescriptor& TPipelineLoader::FetchPipeline(const STRING_TYPE& _pipelineName)
    {
        RESOURCE_DEBUG(_pipelineName<<" is requested");
        auto ite = m_pipelines.find(_pipelineName);
        return ite->second;
    }

}