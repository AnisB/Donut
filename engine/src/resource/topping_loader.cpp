// Bento includes
#include <bento_base/security.h>
#include <bento_collection/dynamic_string.h>
#include <bento_tools/file_system.h>

// Library includes
#include "resource/resource_manager.h"
#include "rapidxml.hpp"
#include "tools/xmlhelpers.h"
#include "resource/toppingloader.h"

// Bento includes
#include <bento_math/types.h>

namespace donut
{
    TToppingLoader::TToppingLoader()
    {

    }


    TToppingLoader::~TToppingLoader()
    {
        
    }

    void TToppingLoader::Init()
    {
        LoadToppings();
    }

    void TToppingLoader::LoadToppings()
    {   
		// Fetch the root asset directory
        const STRING_TYPE& root_asset_dir = ResourceManager::Instance().RootAssetsFolder();
		
		// Look for all the topping files in the target directory 
		bento::Vector<bento::DynamicString> toppingFiles(*bento::common_allocator());
		bento::file_system::collect_files_with_extension(root_asset_dir.c_str(), "topping", toppingFiles);

		// Create a descriptor for
        for(auto& topping : toppingFiles)
        {
			// Parse the descriptor
            TToppingDescriptor newTopping;
            ParseToppingFile(topping.c_str(), newTopping);
			m_toppings[newTopping.name] = newTopping;
        }
    }
}