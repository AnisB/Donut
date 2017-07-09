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
* You should have received a 
copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/

// Library includes
#include "flourloader.h"

#include "butter/stream.h"

#include "core/sceneNode.h"

#include "tools/fileloader.h"
#include "tools/xmlhelpers.h"

#include "graphics/light.h"
#include "graphics/factory.h"

#include "resource/common.h"
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
        RESOURCE_WARNING("========= FLOUR LOADER INIT =========");
        LoadFlours();
        RESOURCE_WARNING("=====================================");
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
            RESOURCE_INFO("Flour "<< flrDsr.name<<" file: "<< flrDsr.file);
        }
	}

	const TFlourDescriptor& TFlourLoader::FetchFlour(const STRING_TYPE& _flourFileName)
	{
        RESOURCE_DEBUG(_flourFileName<<" is requested");
        auto ite = m_flours.find(_flourFileName);
        ASSERT_MSG((ite!=m_flours.end()), "Sugar model not found: "<<_flourFileName);
        return ite->second;
	}
}