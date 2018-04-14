// Library include
#include "recipe/flourdescriptor.h"
#include "tools/xmlhelpers.h"
#include "tools/fileloader.h"

// External includes
#include "rapidxml.hpp"

namespace donut
{
        // XML file token
        #define FLOUR_NODE_TOKEN "flour"
        #define FLOUR_NAME_TOKEN "name"
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
        
        TNodeDescriptor* HandleSceneNode_D(rapidxml::xml_node<>* _sceneNode);
        TNodeDescriptor* HandleNode_D(rapidxml::xml_node<> *_node);


        TSkyboxDescriptor* HandleSkyboxNode_D(rapidxml::xml_node<> * _skybox)
        {
                rapidxml::xml_attribute<> *location = _skybox->first_attribute(SKYBOX_LOCATION_TOKEN);
                rapidxml::xml_attribute<> *extension = _skybox->first_attribute(SKYBOX_EXTENSION_TOKEN);
                TSkyboxDescriptor* skybox = new TSkyboxDescriptor();
                skybox->location = location->value();
                skybox->extension = extension->value();
                return skybox;
        }

        TNodeDescriptor* HandleNode_D(rapidxml::xml_node<> *_node)
        {
                TNodeDescriptor* nodeDesc = new TNodeDescriptor(false);
                // Setting the attributes
                rapidxml::xml_attribute<> *tmAtt = _node->first_attribute(NODE_TRANSFORM_MATRIX_TOKEN);
                if(tmAtt)
                {
                        nodeDesc->tm = tmAtt->value();
                }

                // Creating the node children
                for(rapidxml::xml_node<> *currentNode = _node->first_node(NODE_TOKEN); currentNode; currentNode = currentNode->next_sibling(NODE_TOKEN))
                {
                        nodeDesc->nodes.push_back(HandleNode_D(currentNode));
                }

                // Creating the scene children
                for(rapidxml::xml_node<> *currentSceneNode = _node->first_node(SCENE_NODE_TOKEN); currentSceneNode; currentSceneNode = currentSceneNode->next_sibling())
                {
                        nodeDesc->nodes.push_back(HandleSceneNode_D(currentSceneNode));
                }
                return nodeDesc;
        }


        TNodeDescriptor* HandleSceneNode_D(rapidxml::xml_node<>* _sceneNode)
        {
                TNodeDescriptor* nodeDesc = new TNodeDescriptor(true);
                // Setting the attributes
                rapidxml::xml_attribute<> *tmAtt = _sceneNode->first_attribute(NODE_TRANSFORM_MATRIX_TOKEN);
                if(tmAtt)
                {
                        nodeDesc->tm = tmAtt->value();
                }

                // Creating the node children
                for(rapidxml::xml_node<> *currentNode = _sceneNode->first_node(NODE_TOKEN); currentNode; currentNode = currentNode->next_sibling())
                {
                        nodeDesc->nodes.push_back(HandleNode_D(currentNode));
                }

                // Creating the scene children
                for(rapidxml::xml_node<> *currentSceneNode = _sceneNode->first_node(SCENE_NODE_TOKEN); currentSceneNode; currentSceneNode = currentSceneNode->next_sibling())
                {
                        nodeDesc->nodes.push_back(HandleSceneNode_D(currentSceneNode));
                }

                // Creating the children
                for(rapidxml::xml_node<> *model = _sceneNode->first_node(MODEL_TOKEN); model; model = model->next_sibling())
                {
                        nodeDesc->models.push_back(model->first_attribute(SUGAR_TOKEN)->value());
                }
                return nodeDesc;
        }

        void HandleLightNode_D(rapidxml::xml_node<> *_light, TLightDescriptor& _desc)
        {
                rapidxml::xml_attribute<> *pos = _light->first_attribute(LIGHT_POS_TOKEN);
                if(pos)
                {
                        _desc.pos = pos->value();
                }

                rapidxml::xml_attribute<> *diff = _light->first_attribute(LIGHT_DIFF_TOKEN);
                if(diff)
                {
                        _desc.diff = diff->value();
                }

                rapidxml::xml_attribute<> *spec = _light->first_attribute(LIGHT_SPEC_TOKEN);
                if(spec)
                {
                        _desc.spec = spec->value();
                }

                rapidxml::xml_attribute<> *ray = _light->first_attribute(LIGHT_RAY_TOKEN);
                if(ray)
                {
                        _desc.ray = ray->value();
                }
        }

        TSHDescriptor* HandleSphericalHarmonics_D(rapidxml::xml_node<> * _SH)
        {
                TSHDescriptor* newSH = new TSHDescriptor();
                newSH->red = _SH->first_attribute(RED_COEFF_SPHERICAL_HARMONICS)->value();
                newSH->green = _SH->first_attribute(GREEN_COEFF_SPHERICAL_HARMONICS)->value();
                newSH->blue = _SH->first_attribute(BLUE_COEFF_SPHERICAL_HARMONICS)->value();
                return newSH;
        }

        void HandleIlluminationNode_D(rapidxml::xml_node<> *_illumination, TIlluminationDescritor& _illuminationDes)
        {
                for(rapidxml::xml_node<> *currentLightSource = _illumination->first_node(); currentLightSource; currentLightSource = currentLightSource->next_sibling())
                {
                        const STRING_TYPE& nodeName = currentLightSource->name();
                        if(nodeName == LIGHT_TOKEN)
                        {       
                                TLightDescriptor light;
                                HandleLightNode_D(currentLightSource, light);
                                _illuminationDes.lights.push_back(light);
                        }
                }
        }

        void ParseFlourFile(const STRING_TYPE& _fileName, TFlourDescriptor& _output)
	{
		// Registering the file name
		_output.file = _fileName;

                // reading the text file
                std::vector<char> buffer;
                ReadFile(_fileName.c_str(), buffer);

                // compute the id
                _output.id = GetFileHash(_fileName);

                // Parsing it
                rapidxml::xml_document<> doc;
                doc.parse<0>(&buffer[0]);

                // Fetching the root sugar node
                rapidxml::xml_node<>* flour = doc.first_node(FLOUR_NODE_TOKEN);
                assert(flour);

                // Fetch the name
                _output.name = flour->first_attribute(FLOUR_NAME_TOKEN)->value();

                // Fetch the pipeline
                rapidxml::xml_node<>* sh = flour->first_node(SPHERICAL_HARMONICS);
                if(sh)
                {
                        _output.sh = HandleSphericalHarmonics_D(sh);
                }

                // Processing the geometry hierachy
                rapidxml::xml_node<> *root = flour->first_node(ROOT_TOKEN);
                if(root)
                {
                        _output.root = HandleNode_D(root);
                }

                // Fetch the pipeline
                rapidxml::xml_node<>* pipeline = flour->first_node(PIPELINE_NODE_TOKEN);
                if(pipeline)
                {
                        _output.pipeline = pipeline->first_attribute(PIPELINE_NAME_TOKEN)->value();
                }
                else
                {
                        _output.pipeline = "minimal";
                }

                // Processing the illumination structures
                rapidxml::xml_node<> *illumination = flour->first_node(ILLUMINATION_TOKEN);
                if(illumination)
                {
                        HandleIlluminationNode_D(illumination, _output.illumination);
                }

                // Processing the skybox
                rapidxml::xml_node<> *skybox = flour->first_node(SKYBOX_TOKEN);
                if(skybox)
                {
                        _output.skybox = HandleSkyboxNode_D(skybox);
                }
	}


        bool HasChanged(const TFlourDescriptor& _flourDescriptor)
        {
                RECIPE_GUID id = GetFileHash(_flourDescriptor.file);
                return id != _flourDescriptor.id;
        }
}