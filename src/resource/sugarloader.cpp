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
#include "sugarloader.h"
#include "base/stringhelper.h"
#include "resourcemanager.h"
#include "resource/common.h"
#include "resource/shaderfilehandler.h"
#include "tools/fileloader.h"
#include "butter/types.h"
#include "butter/stream.h"
#include "rapidxml.hpp"
#include "tools/xmlhelpers.h"
#include "recipe/sugar_descriptor.h"

// STL includes
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fstream>



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
        RESOURCE_WARNING("========= SUGAR LOADER INIT =========");
        LoadSugars();
        RESOURCE_WARNING("=====================================");
    }

    void TSugarLoader::LoadSugars()
    {   
        const STRING_TYPE& rootAssetDirectory = ResourceManager::Instance().RootAssetsFolder();
        STRING_TYPE sugarDirectory(rootAssetDirectory + "/common/sugars");

        std::vector<STRING_TYPE> sugarFiles;
        GetExtensionFileList(sugarDirectory, ".sugar", sugarFiles);
        for(auto& sugar : sugarFiles)
        {
            TSugarDescriptor newSugar;
            ParseSugarFile(sugar, newSugar);
            FSugars[newSugar._name] = newSugar;
            RESOURCE_INFO("Sugar "<< newSugar._name<<" file: "<< sugar);
        }
    }

    const TSugarDescriptor& TSugarLoader::FetchSugar(const STRING_TYPE& parModel)
    {
        RESOURCE_DEBUG(parModel<<" is requested");
        auto ite = FSugars.find(parModel);
        ASSERT_MSG((ite!=FSugars.end()), "Sugar model not found: "<<parModel);
        return ite->second;
    }

}