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


#include "light.h"
#include <butter/vector4.h>

#define LIGHT_VERTEX "shaders/light/vertex.glsl"
#define LIGHT_GEOMETRY "shaders/light/geometry.glsl" 
#define LIGHT_FRAGMENT "shaders/light/fragment.glsl" 

#define DEFAULT_RAY 100 
namespace Donut
 {
	TLight::TLight()
	: FShader(0,LIGHT_VERTEX, BASIC_SHADER, BASIC_SHADER, BASIC_SHADER, LIGHT_FRAGMENT)
	, FPosition()
	, FDiff()
	, FSpec()
	, FRayon(DEFAULT_RAY)
	, FOutDate(true)
	{
		FPosition = vector3(0.0);
		FDiff = vector4(1.0);
		FSpec = vector4(0.0);
		ShaderManager::Instance().CreateShader(FShader);
		ShaderManager::Instance().InjectVec3(FShader, FPosition,"lightSource.position");
		ShaderManager::Instance().InjectVec4(FShader, FDiff ,"lightSource.diffuse");
		ShaderManager::Instance().InjectVec4(FShader, FSpec ,"lightSource.specular");	
		ShaderManager::Instance().InjectFloat(FShader, FRayon ,"lightSource.ray");	
	}
	TLight::~TLight()
	{
		
	}
 	void TLight::Bind()
 	{
		ShaderManager::Instance().EnableShader(FShader);
 	}

 	void TLight::Unbind()
 	{
		ShaderManager::Instance().DisableShader();
	}
	void TLight::Translate(const Vector3& parVector)
	{
		FPosition= FPosition + parVector;
		FOutDate = true;
	}

	void TLight::SetPosition(const Vector3& parVector)
	{
		FPosition=parVector;
		FOutDate = true;	
	}
	void TLight::SetColor(const Vector4& parColor)
	{
		FSpec=parColor;
	}
 	void TLight::UpdateCamera(const Matrix4& parProjection, const Matrix4& parView)
 	{
		ShaderManager::Instance().InjectMat4(FShader,parView,"view");
		ShaderManager::Instance().InjectMat4(FShader,parProjection,"projection");
 	}
	void TLight::InjectData()
	{
		if(FOutDate)
		{
			ShaderManager::Instance().InjectVec3(FShader, FPosition,"lightSource.position");
			ShaderManager::Instance().InjectVec4(FShader, FDiff ,"lightSource.diffuse");
			ShaderManager::Instance().InjectVec4(FShader, FSpec ,"lightSource.specular");	
			ShaderManager::Instance().InjectFloat(FShader, FRayon ,"lightSource.ray");	
		}
	}
 }
