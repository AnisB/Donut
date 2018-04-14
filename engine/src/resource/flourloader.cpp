// Library includes
#include "resource/flourloader.h"

#include "butter/stream.h"

#include "core/sceneNode.h"

#include "tools/fileloader.h"
#include "tools/xmlhelpers.h"

#include "graphics/light.h"
#include "graphics/factory.h"
#include "bento_base/log.h"

#include "resource/resourcemanager.h"

// External includes
#include "rapidxml.hpp"
#include <fstream>


namespace donut
{
	TFlourLoader::TFlourLoader()
	{

	}

	TFlourLoader::~TFlourLoader()
	{
		
	}
	
    void TFlourLoader::Init()
    {
        bento::default_logger()->log(bento::LogLevel::debug, "RESOURCE", "========= FLOUR LOADER INIT =========");
        LoadFlours();
		bento::default_logger()->log(bento::LogLevel::debug, "RESOURCE", "=====================================");
	}

	void TFlourLoader::LoadFlours()
	{
		const STRING_TYPE& root_asset_dir = ResourceManager::Instance().RootAssetsFolder();

        std::vector<STRING_TYPE> flourFiles;
        get_all_files_with_extension(root_asset_dir.c_str(), ".flour", flourFiles);
        for(auto& flour : flourFiles)
        {
        	TFlourDescriptor flrDsr;
        	ParseFlourFile(flour, flrDsr);
        	m_flours[flrDsr.name] = flrDsr;
        }
	}

	const TFlourDescriptor& TFlourLoader::FetchFlour(const STRING_TYPE& _flourFileName)
	{
        auto ite = m_flours.find(_flourFileName);
        return ite->second;
	}
}