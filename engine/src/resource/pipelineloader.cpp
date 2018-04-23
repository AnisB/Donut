// Bento includes
#include <bento_base/security.h>
#include <bento_tools/file_system.h>

// Library includes
#include "resource/pipelineloader.h"
#include "tools/xmlhelpers.h"

#include "resource/resource_manager.h"
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
        LoadPipelines();
    }

    void TPipelineLoader::LoadPipelines()
    {   
        const STRING_TYPE& root_asset_dir = ResourceManager::Instance().RootAssetsFolder();

        bento::Vector<bento::DynamicString> pipelineFiles(*bento::common_allocator());
		bento::file_system::collect_files_with_extension(root_asset_dir.c_str(), "pipeline", pipelineFiles);
        for(auto& pipeline : pipelineFiles)
        {
            TPipelineDescriptor newPipeline;
            ParsePipelineFile(pipeline.c_str(), newPipeline);
            m_pipelines[newPipeline.name] = newPipeline;
        }
    }
   
    const TPipelineDescriptor& TPipelineLoader::FetchPipeline(const STRING_TYPE& _pipelineName)
    {
        auto ite = m_pipelines.find(_pipelineName);
        return ite->second;
    }

}