// Library includes
#include "tools/xmlhelpers.h"
#include "tools/fileloader.h"

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
	void BuildShaderDescriptor(rapidxml::xml_node<>* _shaderNode, TShader& _shader)
	{
		// 
		ASSERT_POINTER_NOT_NULL_NO_RELEASE(_shaderNode);
		
        // Fetch vertex shader
        rapidxml::xml_node<>* vertex = _shaderNode->first_node(VERTEX_SHADER_NODE_TOKEN);
        if(vertex)
        {
            _shader.FVertexShader = TShaderFileHandler::Instance().RegisterShaderFile(vertex->first_attribute(SHADER_LOCATION)->value());
        }

        // Fetch tesscontrol shader
        rapidxml::xml_node<>* tesscontrol = _shaderNode->first_node(TESS_CONTROL_SHADER_NODE_TOKEN);
        if(tesscontrol)
        {
            _shader.FTessControl = TShaderFileHandler::Instance().RegisterShaderFile(tesscontrol->first_attribute(SHADER_LOCATION)->value());
        }

        // Fetch tesseval shader
        rapidxml::xml_node<>* tesseval = _shaderNode->first_node(TESS_EVAL_SHADER_NODE_TOKEN);
        if(tesseval)
        {
            _shader.FTessEval = TShaderFileHandler::Instance().RegisterShaderFile(tesseval->first_attribute(SHADER_LOCATION)->value());
        }

        // Fetch geometry shader
        rapidxml::xml_node<>* geometry = _shaderNode->first_node(GEOMETRY_SHADER_NODE_TOKEN);
        if(geometry)
        {
            _shader.FGeometryShader = TShaderFileHandler::Instance().RegisterShaderFile(geometry->first_attribute(SHADER_LOCATION)->value());
        }

        // Fetch fragment shader
        rapidxml::xml_node<>* fragment = _shaderNode->first_node(FRAGMENT_SHADER_NODE_TOKEN);
        if(fragment)
        {
            _shader.FFragmentShader = TShaderFileHandler::Instance().RegisterShaderFile(fragment->first_attribute(SHADER_LOCATION)->value());
        }
	}

    // Builds the textures from a xml node
    int BuildTexturesDescriptor(rapidxml::xml_node<>* _texturesNode, std::vector<TTextureInfo>& _textures, int _initialShift)
    {
        int index = _initialShift;
        for(rapidxml::xml_node<>* texture2D = _texturesNode->first_node(TEXTURE_2D_NODE_TOKEN); texture2D; texture2D = texture2D->next_sibling())
        {
            TTextureInfo tex;
            tex.offset = index;
            tex.name = texture2D->first_attribute(TEXTURE_NAME_TOKEN)->value();
            tex.file = texture2D->first_attribute(TEXTURE_FILE_LOCATION_TOKEN)->value();
            _textures.push_back(tex);
            index++;
        }
		return index;
    }
}