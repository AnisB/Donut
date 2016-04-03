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


	TNode* HandleNode(rapidxml::xml_node<> *_node);
	TSceneNode* HandleSceneNode(rapidxml::xml_node<> *_node);


	TFlourLoader::TFlourLoader()
	{

	}

	TFlourLoader::~TFlourLoader()
	{
		
	}
	
	void TFlourLoader::Init()
	{
		/*
		const std::string& rootAssetDirectory = ResourceManager::Instance().RootAssetsFolder();
        std::string floursDirectory(rootAssetDirectory + "/common/flours");

        std::vector<std::string> flourFiles;
        GetExtensionFileList(floursDirectory, ".flour", flourFiles);
        foreach_macro(flour, flourFiles)
        {
            TFlour* newFlour = new TFlour(*flour);
            m_flours[*flour] = newFlour;
            RESOURCE_INFO("Flour "<< newFlour->filename);
        }
        */
	}

	TLight* HandleLightNode(rapidxml::xml_node<> *_light)
	{
		TLight* newLight = new TLight();
		rapidxml::xml_attribute<> *pos = _light->first_attribute(LIGHT_POS_TOKEN);
		if(pos)
		{
			const std::string& posS = pos->value();
			newLight->SetPosition(convertFromString<Vector3>(posS));
		}

		rapidxml::xml_attribute<> *diff = _light->first_attribute(LIGHT_DIFF_TOKEN);
		if(diff)
		{
			const std::string& diffS = diff->value();
			newLight->SetDiffuse(convertFromString<Vector4>(diffS));
		}

		rapidxml::xml_attribute<> *spec = _light->first_attribute(LIGHT_SPEC_TOKEN);
		if(spec)
		{
			const std::string& specularS = spec->value();
			newLight->SetSpecular(convertFromString<Vector4>(specularS));
		}

		rapidxml::xml_attribute<> *ray = _light->first_attribute(LIGHT_RAY_TOKEN);
		if(ray)
		{
			const std::string& rayS = ray->value();
			newLight->SetRay(convertFromString<float>(rayS));
		}
		return newLight;
	}


	TSceneNode* HandleSkyboxNode(rapidxml::xml_node<> * _skybox)
	{
		rapidxml::xml_attribute<> *location = _skybox->first_attribute(SKYBOX_LOCATION_TOKEN);
		rapidxml::xml_attribute<> *extension = _skybox->first_attribute(SKYBOX_EXTENSION_TOKEN);
		TSceneNode* node = new TSceneNode();
		TMesh* mesh = CreateSkybox(location->value(), extension->value());
		node->AddDrawable(mesh);
		return node;
	}

	TSphericalHarmonics* HandleSphericalHarmonics(rapidxml::xml_node<> * _SH)
	{
		TSphericalHarmonics* newSH = new TSphericalHarmonics();
		rapidxml::xml_attribute<> *degree = _SH->first_attribute(DEGREE_SPHERICAL_HARMONICS);
		
		std::vector<float> red, green, blue;
		rapidxml::xml_attribute<> *redCoeff = _SH->first_attribute(RED_COEFF_SPHERICAL_HARMONICS);
		stringConvertArray(redCoeff->value(), red);
		rapidxml::xml_attribute<> *greenCoeff = _SH->first_attribute(GREEN_COEFF_SPHERICAL_HARMONICS);
		stringConvertArray(greenCoeff->value(), green);
		rapidxml::xml_attribute<> *blueCoeff = _SH->first_attribute(BLUE_COEFF_SPHERICAL_HARMONICS);
		stringConvertArray(blueCoeff->value(), blue);
		newSH->SetCoeffs(red, green, blue);
		return newSH;
	}

	void HandleIlluminationNode(rapidxml::xml_node<> *_illumination, std::vector<TLight*>& _lights)
	{
		for(rapidxml::xml_node<> *currentLightSource = _illumination->first_node(); currentLightSource; currentLightSource = currentLightSource->next_sibling())
		{
			const std::string& nodeName = currentLightSource->name();
			if(nodeName == LIGHT_TOKEN)
			{
				TLight* lightSource = HandleLightNode(currentLightSource);
				_lights.push_back(lightSource);
			}
			else
			{
				RESOURCE_INFO("Unsupported light source");
			}
		}
	}

	TSceneNode* HandleSceneNode(rapidxml::xml_node<> *_sceneNode)
	{
		TSceneNode* node = new TSceneNode();
		// Setting the attributes
		rapidxml::xml_attribute<> *tmAtt = _sceneNode->first_attribute(NODE_TRANSFORM_MATRIX_TOKEN);
		if(tmAtt)
		{
			const std::string& tmS = tmAtt->value();
			node->SetTransformationMatrix(convertFromString<Matrix4>(tmS));
		}

		// Creating the node children
		for(rapidxml::xml_node<> *currentNode = _sceneNode->first_node(NODE_TOKEN); currentNode; currentNode = currentNode->next_sibling())
		{
			TNode* child = HandleNode(currentNode);
			node->AttachChild(child);
		}

		// Creating the scene children
		for(rapidxml::xml_node<> *currentSceneNode = _sceneNode->first_node(SCENE_NODE_TOKEN); currentSceneNode; currentSceneNode = currentSceneNode->next_sibling())
		{
			TSceneNode* child = HandleSceneNode(currentSceneNode);
			node->AttachChild(child);
		}

		// Creating the children
		for(rapidxml::xml_node<> *model = _sceneNode->first_node(MODEL_TOKEN); model; model = model->next_sibling())
		{
			const std::string& sugarName = model->first_attribute(SUGAR_TOKEN)->value();
			TMesh* drwbl = CreateSugarInstance(sugarName);
			node->AddDrawable(drwbl);
		}
		return node;
	}

	TNode* HandleNode(rapidxml::xml_node<> *_node)
	{
		TNode* node = new TNode();
		// Setting the attributes
		rapidxml::xml_attribute<> *tmAtt = _node->first_attribute(NODE_TRANSFORM_MATRIX_TOKEN);
		if(tmAtt)
		{
			const std::string& tmS = tmAtt->value();
			node->SetTransformationMatrix(convertFromString<Matrix4>(tmS));
		}
		// Creating the scene children
		for(rapidxml::xml_node<> *skybox = _node->first_node(SKYBOX_TOKEN); skybox; skybox = skybox->next_sibling(SKYBOX_TOKEN))
		{
			TSceneNode* child = HandleSkyboxNode(skybox);
			node->AttachChild(child);
		}

		// Creating the node children
		for(rapidxml::xml_node<> *currentNode = _node->first_node(NODE_TOKEN); currentNode; currentNode = currentNode->next_sibling(NODE_TOKEN))
		{
			TNode* child = HandleNode(currentNode);
			node->AttachChild(child);
		}

		// Creating the scene children
		for(rapidxml::xml_node<> *currentSceneNode = _node->first_node(SCENE_NODE_TOKEN); currentSceneNode; currentSceneNode = currentSceneNode->next_sibling())
		{
			TSceneNode* child = HandleSceneNode(currentSceneNode);
			node->AttachChild(child);
		}
		return node;
	}

	TFlour* HandleFlourFile(const std::string& _sceneFileName)
	{
		// Reading json file
		std::vector<char> buffer;
		ReadFile(_sceneFileName.c_str(), buffer);
	    rapidxml::xml_document<> doc;
	    // Parsing it
		doc.parse<0>(&buffer[0]);
		// Fetching the scene node
		rapidxml::xml_node<> *scene = doc.first_node(SCENE_TOKEN);
		ASSERT_NO_RELEASE(scene);

		TFlour* flour = new TFlour(_sceneFileName);
		// Processing the geometry hierachy
		rapidxml::xml_node<> *root = scene->first_node(ROOT_TOKEN);
		if(root)
		{
			flour->root = HandleNode(root);
		}
		std::vector<TLight*> lights;
		// Processing the illumination structures
		rapidxml::xml_node<> *illumination = scene->first_node(ILLUMINATION_TOKEN);
		if(illumination)
		{
			HandleIlluminationNode(illumination, flour->lights);
		}
	
		// Processing the illumination structures
		rapidxml::xml_node<>* pipeline = scene->first_node(PIPELINE_NODE_TOKEN);
		if(pipeline)
		{
			flour->pipelineName = pipeline->first_attribute(PIPELINE_NAME_TOKEN)->value();
		}
		else
		{
			flour->pipelineName = "minimal";
		}
		

		rapidxml::xml_node<> *envSH = scene->first_node(SPHERICAL_HARMONICS);
		if(envSH)
		{
			flour->sh = HandleSphericalHarmonics(envSH);
		}
		else
		{
			RESOURCE_INFO("WTF DUDE");
		}
		return flour;
	}

	TFlour* TFlourLoader::LoadFlour(const std::string& _sceneFileName)
	{
 		size_t stringLength = _sceneFileName.size();
        RESOURCE_INFO(_sceneFileName);
 		return HandleFlourFile(_sceneFileName);
	}

}