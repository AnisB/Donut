//Library include
#include "sugardescriptor.h"
#include "tools/fileloader.h"
#include "tools/xmlhelpers.h"

// External includes
#include "rapidxml.hpp"

namespace Donut
{
	#define TOKEN_VEC3  "vec3"
	#define TOKEN_VEC4  "vec4"
	#define TOKEN_MAT3  "mat3"
	#define TOKEN_MAT4  "mat4"
	#define TOKEN_FLOAT "float"
	#define TOKEN_BOOL  "bool"
	#define TOKEN_INT   "int"

    // SUGAR DATA
    #define SUGAR_ROOT_TOKEN "sugar"
    #define SUGAR_NAME_TOKEN "name"

    // GEOMETRY DATA
    #define GEOMETRY_NODE_TOKEN "geometry"
    #define GEOMETRY_TYPE_TOKEN "type"
    #define GEOMETRY_LOCATION_TOKEN "location"

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
    #define TEXTURE_2D_NODE_TOKEN "texture2D"
    #define TEXTURE_NAME_TOKEN "name"
    #define TEXTURE_FILE_LOCATION_TOKEN "location"
    
    // Returns the enumeration that matches a given string    
    void DataTypeToUniform(const STRING_TYPE& _type, const std::string& _name, const std::string& _value, TUniformHandler& _handler)
    {
        if(_type == TOKEN_VEC3)
        {
            _handler.SetValue(TShaderData::VEC3, _name, Vector3());
        }
        else if(_type == TOKEN_VEC4)
        {
            _handler.SetValue(TShaderData::VEC4, _name, Vector4());
        }
        else if(_type == TOKEN_MAT3)
        {
            _handler.SetValue(TShaderData::MAT3, _name, Matrix3());
        }
        else if(_type == TOKEN_MAT4)
        {
            _handler.SetValue(TShaderData::MAT4, _name, Matrix4());
        }
        else if(_type == TOKEN_FLOAT)
        {
            _handler.SetValue(TShaderData::FLOAT, _name, convertFromString<float>(_value));
        }
        else if(_type == TOKEN_INT)
        {
            _handler.SetValue(TShaderData::INTEGER, _name, convertFromString<int>(_value));
        }
        else
        {
            ASSERT_FAIL_MSG("Unsupported uniform type "<<_type);
        }
    }

    void ParseSugarFile(const STRING_TYPE& _fileLocation, TSugarDescriptor& _sugar)
    {
        // reading the text file
        std::vector<char> buffer;
        ReadFile(_fileLocation.c_str(), buffer);

        // compute the GUID
        _sugar.id = GenerateGUID(&buffer[0]);

        // Parsing it
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);

        // Fetching the root sugar node
        rapidxml::xml_node<>* sugar_root = doc.first_node(SUGAR_ROOT_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(sugar_root);

        // Fetching the name
        _sugar.name = sugar_root->first_attribute(SUGAR_NAME_TOKEN)->value();

        // Fetching the geometry
        rapidxml::xml_node<>* geometry = sugar_root->first_node(GEOMETRY_NODE_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(geometry);
        {
            _sugar.geometry = geometry->first_attribute(GEOMETRY_LOCATION_TOKEN)->value();
        }
        
        // Fetching the shader data
        rapidxml::xml_node<>* shaderNode = sugar_root->first_node(SHADER_NODE_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(shaderNode);
        BuildShaderDescriptor(shaderNode, _sugar.material.shader);

        // Fetching external shader data
        rapidxml::xml_node<>* extern_data = sugar_root->first_node(EXTERNAL_DATA_NODE_TOKEN);
        {
            ASSERT_POINTER_NOT_NULL_NO_RELEASE(extern_data);

            // Handeling the floats
            for(rapidxml::xml_node<> *unif = extern_data->first_node(); unif; unif = unif->next_sibling())
            {
                TUniformHandler uni;
                std::string type(unif->first_attribute(UNIFORM_TYPE_TOKEN)->value());
                std::string name(unif->first_attribute(UNIFORM_NAME_TOKEN)->value());
                std::string value(unif->first_attribute(UNIFORM_VALUE_TOKEN)->value());
                DataTypeToUniform(type, name, value, uni);
                _sugar.material.uniforms.push_back(uni);
            }
        }

        // Fetching external shader data
        rapidxml::xml_node<>* textures = sugar_root->first_node(TEXTURES_NODE_TOKEN);
        {
            ASSERT_POINTER_NOT_NULL_NO_RELEASE(textures);
            BuildTexturesDescriptor(textures, _sugar.material.textures);
        }
    }
}