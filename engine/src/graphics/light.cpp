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


#include "graphics/light.h"

// Bento includes
#include <bento_math/vector4.h>

#define DEFAULT_RAY 30
namespace donut
 {
	TLight::TLight()
	: FPosition()
	, FDiff()
	, FSpec()
	, FRayon(DEFAULT_RAY)
	{
		FPosition = bento::vector3(0.0);
		FDiff = bento::vector4(1.0);
		FSpec = bento::vector4(0.0);
	}
	TLight::~TLight()
	{
		
	}

	void TLight::Translate(const bento::Vector3& parVector)
	{
		FPosition= FPosition + parVector;
	}

	void TLight::SetPosition(const bento::Vector3& parVector)
	{
		FPosition=parVector;
	}
	void TLight::SetSpecular(const bento::Vector4& parColor)
	{
		FSpec=parColor;
	}
	void TLight::SetDiffuse(const bento::Vector4& parColor)
	{
		FDiff=parColor;
	}

	void TLight::InjectData(const TShader& _shader, size_t _lightIndex)
	{
		STRING_TYPE shift = "[" + convert_to_string(_lightIndex) + "]";
		ShaderManager::Instance().Inject<bento::Vector3>(_shader, FPosition, "lightSource"+shift+".position");
		ShaderManager::Instance().Inject<bento::Vector4>(_shader, FDiff , "lightSource"+shift+".diffuse");
		ShaderManager::Instance().Inject<bento::Vector4>(_shader, FSpec , "lightSource"+shift+".specular");
		ShaderManager::Instance().Inject<float>(_shader, FRayon , "lightSource"+shift+".ray");	
	}
 }
