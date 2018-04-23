// Bento includes
#include "bento_math/types.h"
#include "bento_base/stream.h"
#include "bento_collection/vector.h"
#include "bento_tools/file_system.h"

// Library includes
#include "resource/sugar_loader.h"
#include "resource/resource_manager.h"
#include "resource/shaderfilehandler.h"
#include "rapidxml.hpp"
#include "tools/xmlhelpers.h"
#include "recipe/sugar_descriptor.h"

namespace donut
{
    TSugarLoader::TSugarLoader()
    {

    }

    TSugarLoader::~TSugarLoader()
    {
        
    }

    void TSugarLoader::Init()
    {
        LoadSugars();
    }

    void TSugarLoader::LoadSugars()
    {   
        // Fetch the root asset dir
        const STRING_TYPE& root_asset_dir = ResourceManager::Instance().RootAssetsFolder();

        // Grab all the sugar files
		bento::Vector<bento::DynamicString> sugarFiles(*bento::common_allocator());
		bento::file_system::collect_files_with_extension(root_asset_dir.c_str(), "sugar", sugarFiles);

        // Parse them and register them
        for(auto& sugar : sugarFiles)
        {
            TSugarDescriptor newSugar;
            ParseSugarFile(sugar.c_str(), newSugar);
            FSugars[newSugar._name] = newSugar;
        }
    }

    const TSugarDescriptor& TSugarLoader::FetchSugar(const STRING_TYPE& parModel)
    {
        auto ite = FSugars.find(parModel);
        return ite->second;
    }

}