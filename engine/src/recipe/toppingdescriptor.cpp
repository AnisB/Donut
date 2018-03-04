//Library include
#include "recipe/toppingdescriptor.h"
#include "tools/fileloader.h"
#include "tools/xmlhelpers.h"

// External includes
#include "rapidxml.hpp"

namespace donut
{
    // Tokens
    #define TOPPING_ROOT_NODE_TOKEN "topping"
    #define TOPPING_NAME_TOKEN "name"

    #define TOKEN_VEC3  "vec3"
    #define TOKEN_VEC4  "vec4"
    #define TOKEN_MAT3  "mat3"
    #define TOKEN_MAT4  "mat4"
    #define TOKEN_FLOAT "float"
    #define TOKEN_BOOL  "bool"
    #define TOKEN_INT   "int"

    // SHADER DATA
    #define SHADER_NODE_TOKEN "shader"

    // BUILD IN DATA
    #define BUILTIN_DATA_NODE_TOKEN "built_in_data"

    // EXTERNAL DATA
    #define EXTERNAL_DATA_NODE_TOKEN "extern_data"
    #define UNIFORM_TYPE_TOKEN "type"
    #define UNIFORM_VALUE_TOKEN "value"
    #define UNIFORM_NAME_TOKEN "name"

    // TEXTURE DATA
    #define TEXTURES_NODE_TOKEN "textures"
    #define BRDF_NODE_TOKEN "brdfs"
    #define TEXTURE_2D_NODE_TOKEN "texture2D"
    #define TEXTURE_NAME_TOKEN "name"
    #define TEXTURE_FILE_LOCATION_TOKEN "location"
    
    // Returns the enumeration that matches a given string    
    void DataTypeToUniform(const STRING_TYPE& _type, const STRING_TYPE& _name, const STRING_TYPE& _value, TUniformHandler& _handler)
    {
        if(_type == TOKEN_VEC3)
        {
            _handler.SetValue(TShaderData::VEC3, _name, bento::Vector3());
        }
        else if(_type == TOKEN_VEC4)
        {
            _handler.SetValue(TShaderData::VEC4, _name, bento::vector4(1.0, 1.0, 1.0, 1.0));
        }
        else if(_type == TOKEN_MAT3)
        {
            _handler.SetValue(TShaderData::MAT3, _name, bento::Matrix3());
        }
        else if(_type == TOKEN_MAT4)
        {
            _handler.SetValue(TShaderData::MAT4, _name, bento::Matrix4());
        }
        else if(_type == TOKEN_FLOAT)
        {
            _handler.SetValue(TShaderData::FLOAT, _name, convert_from_string<float>(_value));
        }
        else if(_type == TOKEN_INT)
        {
            _handler.SetValue(TShaderData::INTEGER, _name, convert_from_string<int>(_value));
        }
        else
        {
            ASSERT_FAIL_MSG("Unsupported uniform type "<<_type);
        }
    }

    void ParseToppingFile(const STRING_TYPE& _fileLocation, TToppingDescriptor& _topping)
    {
        // reading the text file
        std::vector<char> buffer;
        ReadFile(_fileLocation.c_str(), buffer);

        // Set the file location
        _topping.file = _fileLocation;

        // compute the GUID
        _topping.id = GetFileHash(_fileLocation);

        // Parsing it
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);

        // Fetching the root sugar node
        rapidxml::xml_node<>* topping_root = doc.first_node(TOPPING_ROOT_NODE_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(topping_root);

        // Fetching the name
        _topping.name = topping_root->first_attribute(TOPPING_NAME_TOKEN)->value();

        // Fetching the shader data
        rapidxml::xml_node<>* shaderNode = topping_root->first_node(SHADER_NODE_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(shaderNode);
        BuildShaderDescriptor(shaderNode, _topping.data.shader);

        // Fetching external shader data
        rapidxml::xml_node<>* extern_data = topping_root->first_node(EXTERNAL_DATA_NODE_TOKEN);
        {
            ASSERT_POINTER_NOT_NULL_NO_RELEASE(extern_data);

            // Handeling the floats
            for(rapidxml::xml_node<> *unif = extern_data->first_node(); unif; unif = unif->next_sibling())
            {
                TUniformHandler uni;
                STRING_TYPE type(unif->first_attribute(UNIFORM_TYPE_TOKEN)->value());
                STRING_TYPE name(unif->first_attribute(UNIFORM_NAME_TOKEN)->value());
                STRING_TYPE value(unif->first_attribute(UNIFORM_VALUE_TOKEN)->value());
                DataTypeToUniform(type, name, value, uni);
                _topping.data.uniforms.push_back(uni);
            }
        }

		int shift = 0;
        // Fetching external shader data
        rapidxml::xml_node<>* textures = topping_root->first_node(TEXTURES_NODE_TOKEN);
		if(textures)
        {
			shift = BuildTexturesDescriptor(textures, _topping.data.textures, shift);
        }
    }

    bool HasChanged(const TToppingDescriptor& _toppingDescriptor)
    {
        RECIPE_GUID id = GetFileHash(_toppingDescriptor.file);
        return id != _toppingDescriptor.id;
    }
}