// Bento include
#include <bento_base/security.h>
#include <bento_collection/vector.h>
#include <bento_tools/file_system.h>
#include <bento_math/types.h>
#include <bento_math/vector3.h>
#include <bento_math/vector4.h>

// Internal include
#include "base/stringhelper.h"
#include "resource/topping_descriptor.h"
#include "tools/xmlhelpers.h"
#include "graphics/uniformhandler.h"

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
    void DataTypeToUniform(const std::string& _type, const char* _name, const std::string& _value, TUniform& _handler)
    {
        if(_type == TOKEN_VEC3)
        {
            _handler.set_data(TShaderDataType::VEC3, _name, bento::Vector3());
        }
        else if(_type == TOKEN_VEC4)
        {
            _handler.set_data(TShaderDataType::VEC4, _name, bento::vector4(1.0, 1.0, 1.0, 1.0));
        }
        else if(_type == TOKEN_MAT3)
        {
            _handler.set_data(TShaderDataType::MAT3, _name, bento::Matrix3());
        }
        else if(_type == TOKEN_MAT4)
        {
            _handler.set_data(TShaderDataType::MAT4, _name, bento::Matrix4());
        }
        else if(_type == TOKEN_FLOAT)
        {
            _handler.set_data(TShaderDataType::FLOAT, _name, convert_from_string<float>(_value));
        }
        else if(_type == TOKEN_INT)
        {
            _handler.set_data(TShaderDataType::INTEGER, _name, convert_from_string<int>(_value));
        }
        else
        {
            assert_fail_msg("Unsupported uniform type");
        }
    }

	// Converts a string into a type
	TShaderDataType string_to_data_type(const char* type)
	{
		if (strcmp(type, TOKEN_VEC3) == 0)
		{
			return TShaderDataType::VEC3;
		}
		else if (strcmp(type, TOKEN_VEC4) == 0)
		{
			return TShaderDataType::VEC4;
		}
		else if (strcmp(type, TOKEN_MAT3) == 0)
		{
			return TShaderDataType::MAT3;
		}
		else if (strcmp(type, TOKEN_MAT4) == 0)
		{
			return TShaderDataType::MAT4;
		}
		else if (strcmp(type, TOKEN_FLOAT) == 0)
		{
			return TShaderDataType::FLOAT;
		}
		else if (strcmp(type, TOKEN_INT) == 0)
		{
			return TShaderDataType::INTEGER;
		}
		return TShaderDataType::CUBEMAP;
	}

	bool read_topping(const char* target_path, TToppingDescriptor& descriptor)
	{
		// reading the text file
		bento::Vector<char> buffer(*bento::common_allocator());
		bento::read_file(target_path, buffer, bento::FileType::Text);

        // Parsing it
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);

        // Fetching the root sugar node
        rapidxml::xml_node<>* topping_root = doc.first_node(TOPPING_ROOT_NODE_TOKEN);
        assert(topping_root);

        // Fetching the name
        descriptor.name = topping_root->first_attribute(TOPPING_NAME_TOKEN)->value();

        // Fetching the shader data
        rapidxml::xml_node<>* shaderNode = topping_root->first_node(SHADER_NODE_TOKEN);
        assert(shaderNode);
        BuildShaderPipelineDescriptor(shaderNode, descriptor.shader_pipeline);

        // Fetching external shader data
        rapidxml::xml_node<>* extern_data = topping_root->first_node(EXTERNAL_DATA_NODE_TOKEN);
		if(extern_data != nullptr)
        {
            // Handeling the floats
            for(rapidxml::xml_node<> *unif = extern_data->first_node(); unif; unif = unif->next_sibling())
            {
				uint32_t topping_idx = descriptor.data.size();
				descriptor.data.resize(topping_idx + 1);
				TShaderDataDescriptor& shader_data = descriptor.data[topping_idx];
				shader_data.type = (uint8_t)string_to_data_type(unif->first_attribute(UNIFORM_TYPE_TOKEN)->value());
				shader_data.slot = (unif->first_attribute(UNIFORM_NAME_TOKEN)->value());
				shader_data.data = (unif->first_attribute(UNIFORM_VALUE_TOKEN)->value());
            }
        }

        // Fetching external shader data
        rapidxml::xml_node<>* textures = topping_root->first_node(TEXTURES_NODE_TOKEN);
		if(textures)
        {
			BuildTexturesDescriptor(textures, descriptor.data);
        }

		return true;
	}
}