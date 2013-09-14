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



#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include "Base/Singleton.h"
#include "Texture.h"
#include <string>
#include <map>

 namespace Donut 
 {
 	class TextureManager : public Singleton<TextureManager>
 	{
 	public:
 		TextureManager();
 		~TextureManager();
		TTexture* LoadTexture(const std::string&  parTextureName);
		TTexture* GetTexture(const std::string&  parTextureName);

	private:
		std::map<std::string, TTexture*> FTextures;
	};
}

#endif // TEXTURE_MANAGER
