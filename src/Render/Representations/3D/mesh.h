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


 #ifndef DONUT_MESH
 #define DONUT_MESH

#include "Render/DrawableObject.h"
#include "resource/sugar.h"
#include "resource/model.h"
#include "resource/texture.h"
#include "MultiThread/ThreadSharedObject.h"
#include "Math/vec.h"

 namespace Donut
 {
	class TMesh : public TDrawableObject, public TThreadSharedObject
	{
	public:
	 	TMesh(TVec3 parPosition, const std::string& parSugarName);
	 	~TMesh();

	 	virtual void AddTexture(TTexture* parTex, const std::string& parName);
	 	virtual void Init();
	 	virtual void Draw();

	 	void SetPosition(const TVec3& parPos);
 		virtual void UpdateInfoShader(const Matrix4& parModelMatrix, Camera* parCamera);

	protected:
	 	TVec3 FPosition;

	 	// Model to draw
	 	TSugar FSugarModel;
	 	TModel* FModel;
	 };
}
 #endif // DONUT_MESH