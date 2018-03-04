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

#pragma once

// library includs
#include "graphics/ShaderManager.h"


// Bento includes
#include <bento_math/Vector3.h>
 
 namespace donut
 {
	class TLight
	{
	public:
		TLight();
		~TLight();
		void Translate(const bento::Vector3& _vector);
		void SetPosition(const bento::Vector3& _vector);
		void SetSpecular(const bento::Vector4& _color);
		void SetDiffuse(const bento::Vector4& _color);
		void SetRay(float _ray) {FRayon = _ray;}
		void InjectData(const TShader& _shader, size_t _lightIndex);

	protected:
		bento::Vector3 FPosition;
		bento::Vector4 FDiff;
		bento::Vector4 FSpec;
		float FRayon;
	};
 }