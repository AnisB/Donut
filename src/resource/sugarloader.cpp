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

// Library includes
#include "sugarloader.h"
#include "base/common.h"
#include "base/stringhelper.h"
#include "resourcemanager.h"
#include "resource/common.h"
#include "resource/shaderfilehandler.h"
#include "tools/fileloader.h"
#include "butter/types.h"
#include "butter/stream.h"
#include "rapidxml.hpp"

// STL includes
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fstream>

#define TOKEN_VEC3  "vec3"
#define TOKEN_VEC4  "vec4"
#define TOKEN_MAT3  "mat3"
#define TOKEN_MAT4  "mat4"
#define TOKEN_FLOAT "float"
#define TOKEN_BOOL  "bool"
#define TOKEN_INT   "int"

namespace Donut
{
    // Returns the first non empty line within a given file stream
    void GetNonEmptyLine(std::ifstream& file, std::string& _outString)
    {
        getline(file, _outString);
        removeMultSpace(_outString);
        while(_outString == "")
        {
            getline(file, _outString);
            removeMultSpace(_outString);
        }
    }

    // Returns the enumeration that matches a given string    
    void DataTypeToUniform(const std::string& _type, const std::string& _name, const std::string& _value, TUniformHandler& _handler)
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

    TSugarLoader::TSugarLoader()
    : FFinished(false)
    {

    }


    TSugarLoader::~TSugarLoader()
    {
        
    }

    void TSugarLoader::Init()
    {
        RESOURCE_WARNING("========= SUGAR LOADER INIT =========");
        LoadSugars();
        RESOURCE_WARNING("=====================================");

    }

    void TSugarLoader::LoadSugars()
    {   
        const std::string& rootAssetDirectory = ResourceManager::Instance().RootAssertFolder();
        std::string sugarDirectory(rootAssetDirectory + "/common/sugars");

        std::vector<std::string> sugarFiles;
        GetExtensionFileList(sugarDirectory, ".sugar", sugarFiles);
        foreach_macro(sugar, sugarFiles)
        {
            const TSugar& newSugar = ParseSugarFile(*sugar);
            FSugars[newSugar.name] = newSugar;
            RESOURCE_INFO("Sugar "<< newSugar.name<<" file: "<< *sugar);
        }
    }

    // SUGAR DATA
    #define SUGAR_ROOT_TOKEN "sugar"
    #define SUGAR_NAME_TOKEN "name"

    // GEOMETRY DATA
    #define GEOMETRY_NODE_TOKEN "geometry"
    #define GEOMETRY_TYPE_TOKEN "type"
    #define GEOMETRY_LOCATION_TOKEN "location"

    // SHADER DATA
    #define SHADER_NODE_TOKEN "shader"
    #define VERTEX_SHADER_NODE_TOKEN "vertex"
    #define TESS_CONTROL_SHADER_NODE_TOKEN "tesscontrol"
    #define TESS_EVAL_SHADER_NODE_TOKEN "tesseval"
    #define GEOMETRY_SHADER_NODE_TOKEN "geometry"
    #define FRAGMENT_SHADER_NODE_TOKEN "fragment"
    #define SHADER_LOCATION "location"

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
    
    TSugar TSugarLoader::ParseSugarFile(const std::string& _fileLocation)
    {
        TSugar sugar;

        // reading the text file
        std::vector<char> buffer;
        ReadFile(_fileLocation.c_str(), buffer);

        // Parsing it
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);

        // Fetching the root sugar node
        rapidxml::xml_node<>* sugar_root = doc.first_node(SUGAR_ROOT_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(sugar_root);

        // Fetching the name
        sugar.name = sugar_root->first_attribute(SUGAR_NAME_TOKEN)->value();

        // Fetching the geometry
        rapidxml::xml_node<>* geometry = sugar_root->first_node(GEOMETRY_NODE_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(geometry);
        {
            sugar.geometry = geometry->first_attribute(GEOMETRY_LOCATION_TOKEN)->value();
        }
        
        // Fetching the shader data
        rapidxml::xml_node<>* shaderNode = sugar_root->first_node(SHADER_NODE_TOKEN);
        ASSERT_POINTER_NOT_NULL_NO_RELEASE(shaderNode);
        {
            // Fetch vertex shader
            rapidxml::xml_node<>* vertex = shaderNode->first_node(VERTEX_SHADER_NODE_TOKEN);
            if(vertex)
            {
                sugar.material.shader.FVertexShader = TShaderFileHandler::Instance().RegisterShaderFile(vertex->first_attribute(SHADER_LOCATION)->value());
            }

            // Fetch tesscontrol shader
            rapidxml::xml_node<>* tesscontrol = shaderNode->first_node(TESS_CONTROL_SHADER_NODE_TOKEN);
            if(tesscontrol)
            {
                sugar.material.shader.FTessControl = TShaderFileHandler::Instance().RegisterShaderFile(tesscontrol->first_attribute(SHADER_LOCATION)->value());
            }

            // Fetch tesseval shader
            rapidxml::xml_node<>* tesseval = shaderNode->first_node(TESS_EVAL_SHADER_NODE_TOKEN);
            if(tesseval)
            {
                sugar.material.shader.FTessEval = TShaderFileHandler::Instance().RegisterShaderFile(tesseval->first_attribute(SHADER_LOCATION)->value());
            }

            // Fetch geometry shader
            rapidxml::xml_node<>* geometry = shaderNode->first_node(GEOMETRY_SHADER_NODE_TOKEN);
            if(geometry)
            {
                sugar.material.shader.FGeometryShader = TShaderFileHandler::Instance().RegisterShaderFile(geometry->first_attribute(SHADER_LOCATION)->value());
            }

            // Fetch fragment shader
            rapidxml::xml_node<>* fragment = shaderNode->first_node(FRAGMENT_SHADER_NODE_TOKEN);
            if(fragment)
            {
                sugar.material.shader.FFragmentShader = TShaderFileHandler::Instance().RegisterShaderFile(fragment->first_attribute(SHADER_LOCATION)->value());
            }
        }

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
                sugar.material.uniforms.push_back(uni);
            }
        }

        // Fetching external shader data
        rapidxml::xml_node<>* textures = sugar_root->first_node(TEXTURES_NODE_TOKEN);
        {
            ASSERT_POINTER_NOT_NULL_NO_RELEASE(textures);
            int index =0;
            // Handeling the floats
            for(rapidxml::xml_node<> *tex2D = textures->first_node(TEXTURE_2D_NODE_TOKEN); tex2D; tex2D = tex2D->next_sibling())
            {
                TTextureInfo tex;
                tex.offset = index;
                tex.name = tex2D->first_attribute(TEXTURE_NAME_TOKEN)->value();
                tex.file = tex2D->first_attribute(TEXTURE_FILE_LOCATION_TOKEN)->value();
                sugar.material.textures.push_back(tex);
                index++;
            }
        }
        return sugar;
    }

    void TSugarLoader::LoadSugars_MultiThread()
    {
        ASSERT_NOT_IMPLEMENTED();
    }

    TSugar TSugarLoader::FetchSugar(const std::string& parModel)
    {
        RESOURCE_DEBUG(parModel<<" is requested");
        auto ite = FSugars.find(parModel);
        ASSERT_MSG((ite!=FSugars.end()), "Sugar model not found: "<<parModel);
        return ite->second;
    }

}