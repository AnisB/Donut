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
#include "base/common.h"
#include "resourcemanager.h"
#include "resource/common.h"
#include "tools/fileloader.h"
#include "butter/types.h"
#include "butter/stream.h"
#include "rapidxml.hpp"
#include "tools/xmlhelpers.h"
#include "resource/toppingloader.h"

// STL includes
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fstream>



namespace Donut
{
    TToppingLoader::TToppingLoader()
    {

    }


    TToppingLoader::~TToppingLoader()
    {
        
    }

    void TToppingLoader::Init()
    {
        RESOURCE_WARNING("========= TOPPING LOADER INIT =========");
        LoadToppings();
        RESOURCE_WARNING("=====================================");
    }

    void TToppingLoader::LoadToppings()
    {   
        const std::string& rootAssetDirectory = ResourceManager::Instance().RootAssetsFolder();
        std::string toppingDirectory(rootAssetDirectory + "/common/toppings");

        std::vector<std::string> toppingFiles;
        GetExtensionFileList(toppingDirectory, ".topping", toppingFiles);
        foreach_macro(topping, toppingFiles)
        {
            TToppingDescriptor newTopping;
            ParseToppingFile(*topping, newTopping);
            m_toppings[newTopping.name] = newTopping;
            RESOURCE_INFO("Topping "<< newTopping.name<<" file: "<< *topping);
        }
    }

    const TToppingDescriptor& TToppingLoader::FetchTopping(const std::string& _toppingFile)
    {
        RESOURCE_DEBUG(_toppingFile<<" is requested");
        auto ite = m_toppings.find(_toppingFile);
        ASSERT_MSG((ite!=m_toppings.end()), "Topping not found: "<<_toppingFile);
        return ite->second;
    }

}