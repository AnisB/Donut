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

#ifndef DONUT_SUGAR
#define DONUT_SUGAR

#include <string>
#include <list>

namespace ShaderDataType
{
    enum Type
    {
        INTEGER,
        FLOAT,
        BOOL,
        VEC3,
        VEC4,
        MAT3,
        MAT4,
        TYPE
    };
}
struct TBuildIn
{
    ShaderDataType::Type dataType;
    std::string name;
};

struct TUniform
{
    ShaderDataType::Type dataType;
    std::string name;
    std::string value;
};

struct TTextureInfo
{
    int index;
    std::string name;
    std::string file;
    unsigned int texID;
    TTextureInfo()
    {
        index=0;
        texID=0;
    }
    TTextureInfo(const TTextureInfo& parTextureInfo)
    {
        index=parTextureInfo.index;
        name=parTextureInfo.name;
        file=parTextureInfo.file;
        texID=parTextureInfo.texID;
    }
};
struct TCubeMapInfo
{
    int index;
    std::string name;
    std::string path;
    unsigned int cmID;
    TCubeMapInfo()
    {
        index=0;
        cmID=0;
    }
    TCubeMapInfo(const TCubeMapInfo& parCubeMapInfo)
    {
        index=parCubeMapInfo.index;
        name=parCubeMapInfo.name;
        path=parCubeMapInfo.path;
        cmID=parCubeMapInfo.cmID;
    }
};
struct TShaderDescr
{
    std::string vertex;
    std::string tessCtrl;
    std::string tessEval;
    std::string fragment;
};

struct TSugar
{
    std::string               name;
	std::string               model;
    std::list<TBuildIn>       builtIns;
    std::list<TUniform>       uniforms;
    std::list<TTextureInfo>   textures;
    std::list<TCubeMapInfo>   cubeMaps;
    TShaderDescr              shader;

    TSugar( )
    {
    }
    TSugar( const TSugar& parSugar)
    {
        name = parSugar.name;
        model = parSugar.model;
        shader = parSugar.shader;
        uniforms = parSugar.uniforms;
        textures = parSugar.textures;
        cubeMaps = parSugar.cubeMaps;
    }

    ~TSugar( )
    {

    }
};

#endif // DONUT_SUGAR
 