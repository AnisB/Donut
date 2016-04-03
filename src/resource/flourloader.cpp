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
#include "flourloader.h"
#include "tools/fileloader.h"
#include "graphics/light.h"
#include "graphics/mesh.h"
#include "graphics/factory.h"
#include "core/sceneNode.h"
#include "resource/common.h"
#include "resource/resourcemanager.h"
#include "base/common.h"
#include "butter/stream.h"
#include "rapidxml.hpp"
#include "tools/xmlhelpers.h"

#include <fstream>


namespace Donut
{
	// XML file token
	#define SCENE_TOKEN "flour"
	#define ROOT_TOKEN "root"
	#define NODE_TOKEN "node"
	#define SCENE_NODE_TOKEN "scenenode"
	#define MODEL_TOKEN "model"
	#define SUGAR_TOKEN "sugar"
	#define NODE_TRANSFORM_MATRIX_TOKEN "TM"
	// Light data
	#define ILLUMINATION_TOKEN "illumination"
	#define SPHERICAL_HARMONICS "envSH"
	#define DEGREE_SPHERICAL_HARMONICS "degree"
	#define RED_COEFF_SPHERICAL_HARMONICS "red"
	#define GREEN_COEFF_SPHERICAL_HARMONICS "green"
	#define BLUE_COEFF_SPHERICAL_HARMONICS "blue"
	#define LIGHT_TOKEN "light"
	#define LIGHT_POS_TOKEN "pos"
	#define LIGHT_DIFF_TOKEN "diff"
	#define LIGHT_SPEC_TOKEN "spec"
	#define LIGHT_RAY_TOKEN "ray"
	// Skybox data
	#define SKYBOX_TOKEN "skybox"
	#define SKYBOX_EXTENSION_TOKEN "extension"
	#define SKYBOX_LOCATION_TOKEN "location"

	// Pipeline data
	#define PIPELINE_NODE_TOKEN "pipeline"
	#define PIPELINE_NAME_TOKEN "name"


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
		
		const std::string& rootAssetDirectory = ResourceManager::Instance().RootAssetsFolder();
        std::string floursDirectory(rootAssetDirectory + "/common/flours");

        std::vector<std::string> flourFiles;
        GetExtensionFileList(floursDirectory, ".flour", flourFiles);
        foreach_macro(flour, flourFiles)
        {
        	TFlourDescriptor flrDsr;
        	ParseFlourFile(*flour, flrDsr);
        	m_flours[flrDsr.name] = flrDsr;
            RESOURCE_INFO("Flour "<< flrDsr.name<<" file: "<< flrDsr.file);
        }
	}

	const TFlourDescriptor& TFlourLoader::FetchFlour(const std::string& _flourFileName)
	{
        RESOURCE_DEBUG(_flourFileName<<" is requested");
        auto ite = m_flours.find(_flourFileName);
        ASSERT_MSG((ite!=m_flours.end()), "Sugar model not found: "<<_flourFileName);
        return ite->second;
	}
}