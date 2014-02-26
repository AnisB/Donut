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

#ifndef DONUT_SKYBOX
#define DONUT_SKYBOX


#include "Render/DrawableObject.h"
#include "MultiThread/ThreadSharedObject.h"
#include "resource/texture.h"


namespace Donut
{
	class TSkybox : public TDrawableObject, public TThreadSharedObject
	{
	public:
		TSkybox(TSkyboxData::Type parType, TImgType::Type parImageType,const std::string& parPath);
		~TSkybox();
		void Init();
		void Draw();

	protected:
		TSkyboxData::Type FType;
		TImgType::Type FImageType;
		TSkyboxTexture* FTexture;
		std::string FSkyboxLocation;
	};
}
#endif