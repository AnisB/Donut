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


 #include "Image.h"
 #include "Render/Defines.h"
 #include "Texturing/TextureManager.h"
 #include "Base/Common.h"
 #include "MultiThread/Defines.h"


namespace Donut
{
 	TImage::TImage(const std::string& parFileName)
 	{
 		FTexture  = TextureManager::Instance().LoadTexture(parFileName);
 	}
 	TImage::~TImage()
 	{

 	}

 	void TImage::Draw()
 	{
 		glColor4f(FFilter.r,FFilter.g,FFilter.b, FFilter.a);
 		glEnable(GL_TEXTURE_2D);
 		glBindTexture(GL_TEXTURE_2D, FTexture->FID);
 		glBindTexture(GL_TEXTURE_2D, 0);
 		glDisable(GL_TEXTURE_2D);

 	}
 }
