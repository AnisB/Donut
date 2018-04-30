// Library includes
#include "tools/xmlhelpers.h"

namespace donut
{
    // Shader data
    #define VERTEX_SHADER_NODE_TOKEN "vertex"
    #define TESS_CONTROL_SHADER_NODE_TOKEN "tesscontrol"
    #define TESS_EVAL_SHADER_NODE_TOKEN "tesseval"
    #define GEOMETRY_SHADER_NODE_TOKEN "geometry"
    #define FRAGMENT_SHADER_NODE_TOKEN "fragment"
    #define SHADER_LOCATION "location"

    // Textures
    #define TEXTURE_2D_NODE_TOKEN "texture2D"
    #define TEXTURE_NAME_TOKEN "name"
    #define TEXTURE_FILE_LOCATION_TOKEN "location"

    
	// Builds the shader from a given xml_node
	void BuildShaderPipelineDescriptor(rapidxml::xml_node<>* _shaderNode, TShaderPipelineDescriptor& shader_pipeline)
	{
        // Fetch vertex shader
        rapidxml::xml_node<>* vertex = _shaderNode->first_node(VERTEX_SHADER_NODE_TOKEN);
        if(vertex)
        {
			shader_pipeline.vertex = vertex->first_attribute(SHADER_LOCATION)->value();
        }

        // Fetch tesscontrol shader
        rapidxml::xml_node<>* tesscontrol = _shaderNode->first_node(TESS_CONTROL_SHADER_NODE_TOKEN);
        if(tesscontrol)
        {
			shader_pipeline.tess_control = tesscontrol->first_attribute(SHADER_LOCATION)->value();
        }

        // Fetch tesseval shader
        rapidxml::xml_node<>* tesseval = _shaderNode->first_node(TESS_EVAL_SHADER_NODE_TOKEN);
        if(tesseval)
        {
			shader_pipeline.tess_eval = tesseval->first_attribute(SHADER_LOCATION)->value();
        }

        // Fetch geometry shader
        rapidxml::xml_node<>* geometry = _shaderNode->first_node(GEOMETRY_SHADER_NODE_TOKEN);
        if(geometry)
        {
			shader_pipeline.geometry = geometry->first_attribute(SHADER_LOCATION)->value();
        }

        // Fetch fragment shader
        rapidxml::xml_node<>* fragment = _shaderNode->first_node(FRAGMENT_SHADER_NODE_TOKEN);
        if(fragment)
        {
			shader_pipeline.fragment = fragment->first_attribute(SHADER_LOCATION)->value();
        }
	}

	void BuildUniformsDescriptor(rapidxml::xml_node<>* uniforms_nodes, std::vector<TShaderDataDescriptor>& topping_data)
	{

	}

    void BuildTexturesDescriptor(rapidxml::xml_node<>* _texturesNode, bento::Vector<TShaderDataDescriptor>& topping_data)
    {
        for(rapidxml::xml_node<>* texture2D = _texturesNode->first_node(TEXTURE_2D_NODE_TOKEN); texture2D; texture2D = texture2D->next_sibling())
        {
			uint32_t data_idx = topping_data.size();
			topping_data.resize(data_idx + 1);
			TShaderDataDescriptor& tex_data = topping_data[data_idx];
			tex_data.slot = texture2D->first_attribute(TEXTURE_NAME_TOKEN)->value();
			tex_data.data = texture2D->first_attribute(TEXTURE_FILE_LOCATION_TOKEN)->value();
			tex_data.type = (uint8_t)TShaderDataType::TEXTURE2D;
        }
    }
}