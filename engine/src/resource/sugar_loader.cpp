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
#include "bento_math/types.h"
#include "bento_base/stream.h"

// Library includes
#include "resource/sugar_loader.h"
#include "resource/resourcemanager.h"
#include "resource/shaderfilehandler.h"
#include "tools/fileloader.h"
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
        std::vector<STRING_TYPE> sugarFiles;
		get_all_files_with_extension(root_asset_dir.c_str(), ".sugar", sugarFiles);

        // Parse them and register them
        for(auto& sugar : sugarFiles)
        {
            TSugarDescriptor newSugar;
            ParseSugarFile(sugar, newSugar);
            FSugars[newSugar._name] = newSugar;
        }
    }

    const TSugarDescriptor& TSugarLoader::FetchSugar(const STRING_TYPE& parModel)
    {
        auto ite = FSugars.find(parModel);
        return ite->second;
    }

}