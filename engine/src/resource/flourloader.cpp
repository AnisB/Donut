// Bento includes
#include <bento_collection/dynamic_string.h>
#include <bento_tools/file_system.h>

// Library includes
#include "resource/flourloader.h"
#include "butter/stream.h"
#include "core/sceneNode.h"
#include "tools/xmlhelpers.h"
#include "graphics/light.h"
#include "graphics/factory.h"
#include "bento_base/log.h"
#include "resource/resource_manager.h"

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

		bento::Vector<bento::DynamicString> flourFiles(*bento::common_allocator());
		bento::file_system::collect_files_with_extension(root_asset_dir.c_str(), "flour", flourFiles);

        for(auto& flour : flourFiles)
        {
        	TFlourDescriptor flrDsr;
        	ParseFlourFile(flour.c_str(), flrDsr);
        	m_flours[flrDsr.name] = flrDsr;
        }
	}

	const TFlourDescriptor& TFlourLoader::FetchFlour(const STRING_TYPE& _flourFileName)
	{
        auto ite = m_flours.find(_flourFileName);
        return ite->second;
	}
}