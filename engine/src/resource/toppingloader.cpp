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
#include <bento_base/security.h>

// Library includes
#include "resource/resourcemanager.h"
#include "resource/common.h"
#include "tools/fileloader.h"
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
        RESOURCE_WARNING("========= TOPPING LOADER INIT =========");
        LoadToppings();
        RESOURCE_WARNING("=====================================");
    }

    void TToppingLoader::LoadToppings()
    {   
		// Fetch the root asset directory
        const STRING_TYPE& root_asset_dir = ResourceManager::Instance().RootAssetsFolder();
		
		// Look for all the topping files in the target directory 
        std::vector<STRING_TYPE> toppingFiles;
		get_all_files_with_extension(root_asset_dir.c_str(), ".topping", toppingFiles);

		// Create a descriptor for
        for(auto& topping : toppingFiles)
        {
			// Parse the descriptor
            TToppingDescriptor newTopping;
            ParseToppingFile(topping, newTopping);

			// Append it
			TOPPING_GUID guid = InsertTopping(newTopping);
            RESOURCE_INFO("Topping "<< newTopping.name<<" file: "<< topping);
        }
    }

	// Insert a topping into the local data structures
	TOPPING_GUID TToppingLoader::InsertTopping(TToppingDescriptor& _targetTopping)
	{
		// Append the Index and the geometry
		TOPPING_GUID toppingIndex = m_toppings.size();
		m_toppings.push_back(_targetTopping);
		m_toppingsIdentifiers[_targetTopping.name] = toppingIndex;
		return toppingIndex;
	}

    TOPPING_GUID TToppingLoader::FetchMaterial(const STRING_TYPE& _toppingFile)
    {
        // Log the request
        RESOURCE_DEBUG(_toppingFile<<" is requested");

        // Fetch the identifier
        auto ite = m_toppingsIdentifiers.find(_toppingFile);

        // Just make sure it is defined somewhere
		assert_msg((ite != m_toppingsIdentifiers.end()), "Topping not found");

        // We have to make sure that this topping is loaded into memory before loading it
        TToppingDescriptor& targetTopping = m_toppings[ite->second];

        //  If the sugar is not loaded, load it
        if( !targetTopping.loaded)
        {
            // Load resources into memory
            LoadIntoMemory(targetTopping);
        }

        // return it
        return ite->second;
    }

    void TToppingLoader::LoadIntoMemory(TToppingDescriptor& _targetTopping)
    {
        // Fetch the material to load
        TMaterial& targetMaterial = _targetTopping.data;

        // Request all the textures that this material requires
        for(auto& tex : targetMaterial.textures)
        {
            TTexture* texPtr = ResourceManager::Instance().FetchTexture(tex.file);
			tex.texID = texPtr->FID;
        }

        // Load the shader into memory
        ShaderManager::Instance().CreateShader(targetMaterial.shader);

        // Mark it as loaded
        _targetTopping.loaded = true;
    }
}