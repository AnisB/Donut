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
#include "butter/vector4.h"

#define DEFAULT_RAY 30
namespace donut
 {
	TLight::TLight()
	: FPosition()
	, FDiff()
	, FSpec()
	, FRayon(DEFAULT_RAY)
	{
		FPosition = vector3(0.0);
		FDiff = vector4(1.0);
		FSpec = vector4(0.0);
	}
	TLight::~TLight()
	{
		
	}

	void TLight::Translate(const Vector3& parVector)
	{
		FPosition= FPosition + parVector;
	}

	void TLight::SetPosition(const Vector3& parVector)
	{
		FPosition=parVector;
	}
	void TLight::SetSpecular(const Vector4& parColor)
	{
		FSpec=parColor;
	}
	void TLight::SetDiffuse(const Vector4& parColor)
	{
		FDiff=parColor;
	}

	void TLight::InjectData(const TShader& _shader, size_t _lightIndex)
	{
		STRING_TYPE shift = "[" + convert_to_string(_lightIndex) + "]";
		ShaderManager::Instance().Inject<Vector3>(_shader, FPosition, "lightSource"+shift+".position");
		ShaderManager::Instance().Inject<Vector4>(_shader, FDiff , "lightSource"+shift+".diffuse");
		ShaderManager::Instance().Inject<Vector4>(_shader, FSpec , "lightSource"+shift+".specular");	
		ShaderManager::Instance().Inject<float>(_shader, FRayon , "lightSource"+shift+".ray");	
	}
 }
