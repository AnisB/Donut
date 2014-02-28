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

#include "sugarloader.h"


#include <Base/DebugPrinters.h>
#include <Base/Common.h>

#include <Tools/FileLoader.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <fstream>

namespace Donut
{
    void getNonEmptyLine(std::ifstream& file, std::string& parFile)
    {
        std::getline(file, parFile);
        parFile=removeMultSpace(parFile);
        while(parFile=="")
        {
            std::getline(file, parFile);
            parFile=removeMultSpace(parFile);
        }
    }

    ShaderDataType::Type stringToDataType(const std::string& parFile)
    {
        if(parFile=="vec3")
        {
            return ShaderDataType::VEC3;
        }
        else if(parFile=="vec4")
        {
            return ShaderDataType::VEC4;
        }
        else if(parFile=="mat3")
        {
            return ShaderDataType::MAT3;
        }
        else if(parFile=="mat4")
        {
            return ShaderDataType::MAT4;
        }
        else if(parFile=="float")
        {
            return ShaderDataType::FLOAT;
        }
        else if(parFile=="bool")
        {
            return ShaderDataType::BOOL;
        }
        else if(parFile=="int")
        {
            return ShaderDataType::INTEGER;
        }
        return ShaderDataType::TYPE;
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
            FILE_SYSTEM_ERR("Error in directory: "<< directoryName); 
            FILE_SYSTEM_ERR("Error n°: "<< strerror (errno)); 
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
            FILE_SYSTEM_DEBUG("New Sugar file: "<< directoryNameforParse); 
        }
        if (closedir (directory)) 
        {
            FILE_SYSTEM_ERR("Error while closing directory: "<< directoryName); 
            return;
        }
        FILE_SYSTEM_DEBUG("The parser found: "<<FSugars.size());
    }

    TSugar TSugarLoader::ParseFile(const std::string& parFileName)
    {
        //size_t index = 0;
        TSugar sugar;
        std::ifstream fin(parFileName.c_str());
        std::string file_line;
        std::getline(fin, file_line);
        file_line=removeMultSpace(file_line);
        std::vector<std::string> header = split(file_line,' ');

        CondAssertReleasePrint((header.size()==2) && (header[0]=="Object"),"In file "<<parFileName<<" wrong header.");
        sugar.name = header[1];

        getNonEmptyLine(fin, file_line);
        CondAssertReleasePrint(!(file_line.find("{")>=file_line.size()),"Wrong token@"<< file_line);
        while(!fin.eof())
        {
            getNonEmptyLine(fin, file_line);
            if(file_line.find("model{")!= std::string::npos)
            {
                getNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    // FILE_SYSTEM_DEBUG("The model is: "<<file_line);
                    sugar.model=file_line;
                    getNonEmptyLine(fin, file_line);
                }
            }
            else if(file_line.find("textures{")!= std::string::npos)
            {
                int index = 0;
                getNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    std::vector<std::string> entete = split(file_line,' ');
                    TTextureInfo tex;
                    tex.index = index;
                    tex.name = entete[1];
                    tex.file = entete[2];
                    sugar.textures.push_back(tex);
                    //FILE_SYSTEM_DEBUG(tex.index<<" "<<tex.name<<" "<<tex.file);
                    index++;
                    getNonEmptyLine(fin, file_line);
                }                
            }
            else if(file_line.find("cubemaps{")!= std::string::npos)
            {
                int index = 0;
                getNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    std::vector<std::string> entete = split(file_line,' ');
                    TCubeMapInfo cm;
                    cm.index = index;
                    cm.name = entete[1];
                    cm.path = entete[2];
                    sugar.cubeMaps.push_back(cm);
                    //FILE_SYSTEM_DEBUG(cm.index<<" "<<cm.name<<" "<<cm.file);
                    index++;
                    getNonEmptyLine(fin, file_line);
                }                
            }
            else if(file_line.find("built_in_data{")!= std::string::npos)
            {
                getNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    std::vector<std::string> entete = split(file_line,' ');
                    TBuildIn bi;
                    bi.dataType = stringToDataType(entete[1]);
                    bi.name = entete[2];
                    sugar.builtIns.push_back(bi);
                    //FILE_SYSTEM_DEBUG(bi.dataType<<" "<<bi.name);
                    getNonEmptyLine(fin, file_line);
                }                
            }
            else if(file_line.find("extern_data{")!= std::string::npos)
            {
                getNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    std::vector<std::string> entete = split(file_line,' ');
                    TUniform uni;
                    uni.dataType = stringToDataType(entete[1]);
                    uni.name = entete[2];
                    uni.value = entete[3];
                    sugar.uniforms.push_back(uni);
                    // FILE_SYSTEM_DEBUG(uni.dataType<<" "<<uni.name<<" "<<uni.value);
                    getNonEmptyLine(fin, file_line);
                }                
            }
            else if(file_line.find("shader{")!= std::string::npos)
            {
                getNonEmptyLine(fin, file_line);
                while(file_line.find("}")== std::string::npos)
                {
                    std::vector<std::string> entete = split(file_line,' ');
                    if(entete[1]=="vertex")
                    {
                        sugar.shader.vertex = entete[2];
                        //FILE_SYSTEM_DEBUG("vertex "<<sugar.shader.vertex);
                    }
                    else if(entete[1]=="tesscontrol")
                    {
                        sugar.shader.tesscontrol = entete[2];
                        // FILE_SYSTEM_ERR("tesscontrol "<<sugar.shader.tesscontrol);
                        sugar.shader.isTesselated = true;
                    }
                    else if(entete[1]=="tesseval")
                    {
                        sugar.shader.tesseval = entete[2];
                        // FILE_SYSTEM_ERR("tesseval "<<sugar.shader.tesseval);
                        sugar.shader.isTesselated = true;
                    }
                    else if(entete[1]=="geometry")
                    {
                        sugar.shader.geometry = entete[2];
                    }
                    else if(entete[1]=="fragment")
                    {
                        sugar.shader.fragment = entete[2];
                        //FILE_SYSTEM_DEBUG("fragment "<<sugar.shader.fragment);
                    }

                    getNonEmptyLine(fin, file_line);
                }                
            }
        }
        return sugar;
    }


    void TSugarLoader::LoadSugars_MultiThread()
    {

    }
    TSugar TSugarLoader::GetSugar(const std::string& parModel)
    {
        FILE_SYSTEM_DEBUG("Looking for the sugar "<< parModel);
        typeof(FSugars.begin()) ite = FSugars.find(parModel);
        AssertNoReleasePrint((ite!=FSugars.end()),"Sugar model not found.");
        return ite->second;
    }

}