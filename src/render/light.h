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


#ifndef DONUT_LIGHT
#define DONUT_LIGHT

#include <butter/Vector3.h>
#include <Render/ShaderManager.h>
 
 namespace Donut
 {
	class TLight
	{
	public:
		TLight();
		~TLight();
		void Bind();
		const TShader& GetShader() {return FShader;}
		void Unbind();
		void Translate(const Vector3& parVector);
		void SetPosition(const Vector3& parVector);
		void SetColor(const Vector4& parColor);
		void InjectData();
 		void UpdateCamera(const Matrix4& parProjection, const Matrix4& parView);


	protected:
		Vector3 FPosition;
		Vector4 FDiff;
		Vector4 FSpec;
		float FRayon;
		bool FOutDate;

		TShader FShader;
	};
 }
 #endif // DONUT_LIGHT
