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



#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include "graphics/shaderManager.h"
#include "graphics/geometry.h"

#include "base/singleton.h"
#include "Texture.h"
#include "sugar.h"
#include <string>
#include <vector>
#include <map>

 namespace Donut 
 {
 	class ResourceManager : public Singleton<ResourceManager>
 	{
 	public:
 		ResourceManager();
 		~ResourceManager();
		TTexture* LoadTexture(const std::string&  parTextureName);
		TTexture* GetTexture(const std::string&  parTextureName);
		void LoadTextures(TSugar&  parSugar);


		TSkyboxTexture* LoadSkybox(const std::string&  parTextureName);
		TSkyboxTexture* LoadSkybox(const std::string&  parTextureName,TImgType::Type parType);
		TSkyboxTexture* GetSkybox(const std::string&  parTextureName);
		TGeometry* CreateGeometry(const std::string& _name, const TShader& parShader, float* _dataArray, int _numVert, unsigned* _indexArray, int num_faces);

		TGeometry* GetGeometry(const TShader& parShader, const std::string&  parObjName);
		std::vector<int> LoadObjToTexture(const std::string&  parFileName, std::vector<TTexture*>& parTexturetable);
		void LoadMaterial(const TShader& _shader, const TMaterial& _material); // <<<< should probably be moved

	protected:
		std::map<std::string, TTexture*> FTextures;
		std::map<std::string, TGeometry*> FGeometries;
		std::map<std::string, TSkyboxTexture*> FSkyboxTextures;
	};
}

#endif // RESOURCE_MANAGER
