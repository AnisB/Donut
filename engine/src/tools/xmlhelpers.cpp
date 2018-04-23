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
			shader_pipeline.shaders[0] = TShaderFileHandler::Instance().RegisterShaderFile(vertex->first_attribute(SHADER_LOCATION)->value());
        }

        // Fetch tesscontrol shader
        rapidxml::xml_node<>* tesscontrol = _shaderNode->first_node(TESS_CONTROL_SHADER_NODE_TOKEN);
        if(tesscontrol)
        {
			shader_pipeline.shaders[1] = TShaderFileHandler::Instance().RegisterShaderFile(tesscontrol->first_attribute(SHADER_LOCATION)->value());
        }

        // Fetch tesseval shader
        rapidxml::xml_node<>* tesseval = _shaderNode->first_node(TESS_EVAL_SHADER_NODE_TOKEN);
        if(tesseval)
        {
			shader_pipeline.shaders[2] = TShaderFileHandler::Instance().RegisterShaderFile(tesseval->first_attribute(SHADER_LOCATION)->value());
        }

        // Fetch geometry shader
        rapidxml::xml_node<>* geometry = _shaderNode->first_node(GEOMETRY_SHADER_NODE_TOKEN);
        if(geometry)
        {
			shader_pipeline.shaders[3] = TShaderFileHandler::Instance().RegisterShaderFile(geometry->first_attribute(SHADER_LOCATION)->value());
        }

        // Fetch fragment shader
        rapidxml::xml_node<>* fragment = _shaderNode->first_node(FRAGMENT_SHADER_NODE_TOKEN);
        if(fragment)
        {
			shader_pipeline.shaders[4] = TShaderFileHandler::Instance().RegisterShaderFile(fragment->first_attribute(SHADER_LOCATION)->value());
        }
	}

	void BuildUniformsDescriptor(rapidxml::xml_node<>* uniforms_nodes, std::vector<TShaderDataDescriptor>& topping_data)
	{

	}

    void BuildTexturesDescriptor(rapidxml::xml_node<>* _texturesNode, std::vector<TShaderDataDescriptor>& topping_data)
    {
        for(rapidxml::xml_node<>* texture2D = _texturesNode->first_node(TEXTURE_2D_NODE_TOKEN); texture2D; texture2D = texture2D->next_sibling())
        {
			TShaderDataDescriptor tex;
            tex._slot = texture2D->first_attribute(TEXTURE_NAME_TOKEN)->value();
            tex._data = texture2D->first_attribute(TEXTURE_FILE_LOCATION_TOKEN)->value();
			tex._type = TShaderData::TEXTURE2D;
			topping_data.push_back(tex);
        }
    }
}