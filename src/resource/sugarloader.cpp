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
#include "resource/common.h"
#include "resource/shaderfilehandler.h"
#include "tools/fileloader.h"
#include "butter/types.h"

// STL includes
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
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
        _outString = removeMultSpace(_outString);
        while(_outString == "")
        {
            getline(file, _outString);
            _outString = removeMultSpace(_outString);
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
            _handler.SetValue(TShaderData::FLOAT, _name, stringConvert<float>(_value));
        }
        else if(_type == TOKEN_INT)
        {
            _handler.SetValue(TShaderData::INTEGER, _name, stringConvert<int>(_value));
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

    void TSugarLoader::SetDirectory(const std::string& parDirectory)
    {
        FMediaPath = parDirectory;
    }

    void TSugarLoader::Init(const std::string& parDirectory)
    {
        RESOURCE_WARNING("========= SUGAR LOADER INIT =========");
        SetDirectory(parDirectory);
        LoadSugars();
        RESOURCE_WARNING("=====================================");

    }

    void TSugarLoader::LoadSugars()
    {   
        // useful vars
        DIR * directory;
        std::string directoryName = FMediaPath.c_str();
        std::string directoryNameforParse = FMediaPath.c_str();
        directoryName+="/sugars";

        // Opening the directory
        directory = opendir (directoryName.c_str());

        if (! directory) 
        {
            RESOURCE_ERROR("Error in directory: "<< directoryName); 
#if __posix__
            RESOURCE_ERROR("Error n°: "<< strerror (errno)); 
#elif WIN32
			char msg[20];
            RESOURCE_ERROR("Error n°: "<< strerror_s (msg, errno)); 
#endif
            return;
        }

        while (1) 
        {
            struct dirent * newEntry;
            newEntry = readdir (directory);
            if (! newEntry) 
            {
                break;
            }
            std::string fileName(newEntry->d_name);
            if((fileName=="..")|| (fileName==".") || fileName.size()<7)
            {
                continue;
            }
            else if(fileName.substr(fileName.size()-6,fileName.size())!=".sugar")
            {
                continue;
            }
            directoryNameforParse = directoryName;
            directoryNameforParse+="/";
            directoryNameforParse+=newEntry->d_name;
            const TSugar& newSugar = ParseFile(directoryNameforParse);
            FSugars[newSugar.name]= newSugar;
            RESOURCE_INFO("Sugar "<< newSugar.name<<" file: "<< directoryNameforParse); 
        }
        if (closedir (directory)) 
        {
            ASSERT_FAIL_MSG("Error while closing directory: "<< directoryName); 
            return;
        }
        RESOURCE_INFO("The parser found "<<FSugars.size()<<" sugars");
    }

    TSugar TSugarLoader::ParseFile(const std::string& parFileName)
    {
        //size_t index = 0;
        TSugar sugar;
        std::ifstream fin(parFileName.c_str());
        std::string file_line;
        std::getline(fin, file_line);
        file_line = removeMultSpace(file_line);
        std::vector<std::string> header;
        split(file_line,' ', header);

        ASSERT_MSG((header.size()==2) && (header[0]=="Object"),"In file "<<parFileName<<" wrong header.");
        sugar.name = header[1];

        GetNonEmptyLine(fin, file_line);
        ASSERT_MSG(!(file_line.find("{")>=file_line.size()),"Wrong token@"<< file_line);
        while(!fin.eof())
        {
            GetNonEmptyLine(fin, file_line);
            if(file_line.find("model{")!= std::string::npos)
            {
                GetNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    RESOURCE_DEBUG("The model is: "<<file_line);
                    sugar.geometry=file_line;
                    GetNonEmptyLine(fin, file_line);
                }
            }
            else if(file_line.find("textures{")!= std::string::npos)
            {
                int index = 0;
                GetNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    std::vector<std::string> entete;
                    split(file_line,' ', entete);
                    TTextureInfo tex;
                    tex.offset = index;
                    tex.name = entete[1];
                    tex.file = entete[2];
                    sugar.material.textures.push_back(tex);
                    //RESOURCE_DEBUG(tex.index<<" "<<tex.name<<" "<<tex.file);
                    index++;
                    GetNonEmptyLine(fin, file_line);
                }                
            }
            else if(file_line.find("cubemaps{")!= std::string::npos)
            {
                int index = 0;
                GetNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    std::vector<std::string> entete;
                    split(file_line,' ', entete);
                    TCubeMapInfo cm;
                    cm.offset = index;
                    cm.name = entete[1];
                    cm.path = entete[2];
                    sugar.material.cubeMaps.push_back(cm);
                    //RESOURCE_DEBUG(cm.index<<" "<<cm.name<<" "<<cm.file);
                    index++;
                    GetNonEmptyLine(fin, file_line);
                }                
            }
            else if(file_line.find("built_in_data{")!= std::string::npos)
            {
                GetNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    std::vector<std::string> entete;
                    split(file_line,' ', entete);
                    TBuildIn bi;
                    //bi.dataType = ToDataType(entete[1]);
                    bi.name = entete[2];
                    sugar.material.builtIns.push_back(bi);
                    //RESOURCE_DEBUG(bi.dataType<<" "<<bi.name);
                    GetNonEmptyLine(fin, file_line);
                }                
            }
            else if(file_line.find("extern_data{")!= std::string::npos)
            {
                GetNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    std::vector<std::string> entete;
                    split(file_line,' ', entete);
                    TUniformHandler uni;
                    DataTypeToUniform(entete[1], entete[2], entete[3], uni);
                    sugar.material.uniforms.push_back(uni);
                    GetNonEmptyLine(fin, file_line);
                }                
            }
            else if(file_line.find("shader{")!= std::string::npos)
            {
                GetNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    std::vector<std::string> entete;
                    split(file_line,' ', entete);
                    if(entete[1]=="vertex")
                    {
						sugar.material.shader.FVertexShader = TShaderFileHandler::Instance().RegisterShaderFile(entete[2]);
                    }
                    else if(entete[1]=="tesscontrol")
                    {
                        sugar.material.shader.FTessControl = TShaderFileHandler::Instance().RegisterShaderFile(entete[2]);
                    }
                    else if(entete[1]=="tesseval")
                    {
                        sugar.material.shader.FTessEval = TShaderFileHandler::Instance().RegisterShaderFile(entete[2]);
                    }
                    else if(entete[1]=="geometry")
                    {
                        sugar.material.shader.FGeometryShader = TShaderFileHandler::Instance().RegisterShaderFile(entete[2]);
                    }
                    else if(entete[1]=="fragment")
                    {
                        sugar.material.shader.FFragmentShader = TShaderFileHandler::Instance().RegisterShaderFile(entete[2]);
                    }

                    GetNonEmptyLine(fin, file_line);
                }                
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
        RESOURCE_INFO(parModel<<" is requested");
        auto ite = FSugars.find(parModel);
        ASSERT_MSG((ite!=FSugars.end()), "Sugar model not found: "<<parModel);
        return ite->second;
    }

}