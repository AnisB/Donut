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
#include "base/common.h"
#include "base/stringhelper.h"
#include "resourcemanager.h"
#include "resource/common.h"
#include "resource/shaderfilehandler.h"
#include "tools/fileloader.h"
#include "butter/types.h"
#include "butter/stream.h"
#include "rapidxml.hpp"
#include "tools/xmlhelpers.h"
#include "recipe/sugardescriptor.h"

// STL includes
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fstream>



namespace Donut
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
        const std::string& rootAssetDirectory = ResourceManager::Instance().RootAssetsFolder();
        std::string sugarDirectory(rootAssetDirectory + "/common/sugars");

        std::vector<std::string> sugarFiles;
        GetExtensionFileList(sugarDirectory, ".sugar", sugarFiles);
        foreach_macro(sugar, sugarFiles)
        {
            TSugarDescriptor newSugar;
            ParseSugarFile(*sugar, newSugar);
            FSugars[newSugar.name] = newSugar;
            RESOURCE_INFO("Sugar "<< newSugar.name<<" file: "<< *sugar);
        }
    }

    const TSugarDescriptor& TSugarLoader::FetchSugar(const std::string& parModel)
    {
        RESOURCE_DEBUG(parModel<<" is requested");
        auto ite = FSugars.find(parModel);
        ASSERT_MSG((ite!=FSugars.end()), "Sugar model not found: "<<parModel);
        return ite->second;
    }

}