// Bento include
#include <bento_collection/vector.h>
#include <bento_tools/file_system.h>

// Library include
#include "base/stringhelper.h"
#include "resource/flour_descriptor.h"
#include "tools/xmlhelpers.h"
#include "butter/stream.h"

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
    #define SKYBOX_SOURCE_TOKEN "source"

    // Pipeline data
    #define PIPELINE_NODE_TOKEN "pipeline"
    #define PIPELINE_NAME_TOKEN "name"
        
    int HandleNode(rapidxml::xml_node<> *_node, bento::Vector<TNodeDescriptor>& node_array)
    {
		// Allocate and grab a new node
		uint32_t new_node_idx = node_array.size();
		node_array.resize(new_node_idx + 1);

		// Override the transform if available	
        rapidxml::xml_attribute<> *tmAtt = _node->first_attribute(NODE_TRANSFORM_MATRIX_TOKEN);
        if(tmAtt)
        {
			node_array[new_node_idx].tm = convert_from_string<bento::Matrix4>(tmAtt->value());
        }

        // Creating the node children
        for(rapidxml::xml_node<> *currentNode = _node->first_node(NODE_TOKEN); currentNode; currentNode = currentNode->next_sibling(NODE_TOKEN))
        {
           uint32_t child_idx = HandleNode(currentNode, node_array);
		   node_array[new_node_idx].children.push_back(child_idx);
        }

		// Creating the children
		for (rapidxml::xml_node<> *model = _node->first_node(MODEL_TOKEN); model; model = model->next_sibling())
		{
			uint32_t new_model_idx = node_array[new_node_idx].models.size();
			node_array[new_node_idx].models.resize(new_model_idx + 1);
			bento::DynamicString& str = node_array[new_node_idx].models[new_model_idx];
			str = model->first_attribute(SUGAR_TOKEN)->value();
		}
		return new_node_idx;
    }

	void HandleLightNode(rapidxml::xml_node<> *_light, TLightDescriptor& _desc)
    {
		rapidxml::xml_attribute<> *pos = _light->first_attribute(LIGHT_POS_TOKEN);
		if(pos)
		{
			_desc.pos = convert_from_string<bento::Vector3>(pos->value());
		}

		rapidxml::xml_attribute<> *diff = _light->first_attribute(LIGHT_DIFF_TOKEN);
		if(diff)
		{
			_desc.diff = convert_from_string<bento::Vector4>(diff->value());
		}

		rapidxml::xml_attribute<> *spec = _light->first_attribute(LIGHT_SPEC_TOKEN);
		if(spec)
		{
			_desc.spec = convert_from_string<bento::Vector4>(spec->value());
		}

		rapidxml::xml_attribute<> *ray = _light->first_attribute(LIGHT_RAY_TOKEN);
		if(ray)
		{
			_desc.ray = convert_from_string<float>(spec->value());
		}
	}

	void convert_coeffs(const std::vector<std::string>& coeffs, float* out_data)
	{
		for (uint32_t coeff_idx = 0; coeff_idx < 9; ++coeff_idx)
		{
			out_data[coeff_idx] = convert_from_string<float>(coeffs[coeff_idx]);
		}
	}

	void HandleSphericalHarmonics(rapidxml::xml_node<> * _SH, TSHDescriptor& sh)
	{
		std::string str;
		std::vector<std::string> coeffs;
		{
			str = _SH->first_attribute(RED_COEFF_SPHERICAL_HARMONICS)->value();
			split(str, ' ', coeffs);
			convert_coeffs(coeffs, sh.red);
		}
		{
			str = _SH->first_attribute(GREEN_COEFF_SPHERICAL_HARMONICS)->value();
			split(str, ' ', coeffs);
			convert_coeffs(coeffs, sh.green);
		}
		{
			str = _SH->first_attribute(BLUE_COEFF_SPHERICAL_HARMONICS)->value();
			split(str, ' ', coeffs);
			convert_coeffs(coeffs, sh.blue);
		}
	}

	void HandleIlluminationNode(rapidxml::xml_node<> *_illumination, bento::Vector<TLightDescriptor>& light_array)
	{
		for(rapidxml::xml_node<> *currentLightSource = _illumination->first_node(); currentLightSource; currentLightSource = currentLightSource->next_sibling())
		{
			const std::string nodeName = currentLightSource->name();
			if(nodeName == LIGHT_TOKEN)
			{       
				uint32_t new_light_idx = light_array.size();
				light_array.resize(new_light_idx + 1);

				TLightDescriptor& light = light_array[new_light_idx];
				HandleLightNode(currentLightSource, light);
			}
		}
	}

    bool read_flour(const char* file_location, TFlourDescriptor& _output)
	{
		// reading the text file
		bento::Vector<char> buffer(*bento::common_allocator());
		bento::read_file(file_location, buffer, bento::FileType::Text);

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
            HandleSphericalHarmonics(sh, _output.sh);
			_output.sh.active = true;
		}
		else
		{
			_output.sh.active = false;
		}

        // Processing the geometry hierachy
        rapidxml::xml_node<> *root = flour->first_node(ROOT_TOKEN);
        if(root)
        {
            HandleNode(root, _output.nodes);
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
                HandleIlluminationNode(illumination, _output.lights);
        }

        // Processing the skybox
        rapidxml::xml_node<> *skybox = flour->first_node(SKYBOX_TOKEN);
        if(skybox)
        {
                _output.skybox = skybox->first_attribute(SKYBOX_SOURCE_TOKEN)->value();
        }
		return true;
	}
}