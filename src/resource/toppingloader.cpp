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

    const TMaterial* TToppingLoader::FetchMaterial(const std::string& _toppingFile)
    {
        // Log it
        RESOURCE_DEBUG(_toppingFile<<" is requested");

        // Fetch it
        auto ite = m_toppings.find(_toppingFile);

        // Just make sure it is defined somewhere
        ASSERT_MSG((ite!=m_toppings.end()), "Topping not found: "<<_toppingFile);

        // We have to make sure that this topping is loaded into memory before loading it
        TToppingDescriptor& targetTopping = ite->second;

        //  If the sugar is not loaded, load it
        if( !targetTopping.loaded)
        {
            // Load resources into memory
            LoadIntoMemory(targetTopping);
        }

        // return it
        return &(ite->second.data);
    }

    void TToppingLoader::LoadIntoMemory(TToppingDescriptor& _targetTopping)
    {
        // Fetch the material to load
        TMaterial& targetMaterial = _targetTopping.data;

        // Request all the textures that this material requires
        foreach_macro(tex, targetMaterial.textures)
        {
            TTexture* texPtr = ResourceManager::Instance().FetchTexture(tex->file);
            tex->texID = texPtr->FID;
        }

        foreach_macro(brdfIT, targetMaterial.brfds)
        {
            TGGXBRDF* brdf = ResourceManager::Instance().FetchBRDF(brdfIT->file);
            brdf->id = brdfIT->texID;
        }

        // Load the shader into memory
        ShaderManager::Instance().CreateShader(targetMaterial.shader);

        // Mark it as loaded
        _targetTopping.loaded = true;
    }
}