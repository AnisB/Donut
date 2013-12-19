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

 #include "ResourceManager.h"

 #include "TextureHelpers.h"

 namespace Donut
 {
 	ResourceManager::ResourceManager()
 	{

 	}

 	ResourceManager::~ResourceManager()
 	{

 	}
 	TTexture* ResourceManager::LoadTexture(const std::string&  parTextureName)
 	{
 		typeof(FTextures.begin()) it = FTextures.find(parTextureName);
 		if(it != FTextures.end())
 		{
 			return it->second;
 		}
 		else
 		{
 			TTexture * texture =  TextureHelpers::LoadTexture(parTextureName);
 			FTextures[parTextureName] = texture;
 			glBindTexture(GL_TEXTURE_2D, texture->FID);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_PRIORITY, 1.0); 
 			glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->FWidth, texture->FHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, texture->FData);
 			glBindTexture(GL_TEXTURE_2D, 0);
 		}
 		return NULL;
 	}

 	TTexture* ResourceManager::GetTexture(const std::string&  parTextureName)
 	{
 		typeof(FTextures.begin()) it = FTextures.find(parTextureName);
 		if(it != FTextures.end())
 		{
 			return it->second;
 		}
 		return NULL;
 	}
}