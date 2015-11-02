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
 #include "resource/Common.h"
 #include "input/Common.h"
 #include <Base/Common.h>
 #include <Render/Helper.h>
 #include <Tools/FileLoader.h>
 #include "Base/Macro.h"

 #include <fstream>
 #include <sstream> 
 #include <vector> 
 #include <list> 

 using namespace std;
 
 namespace Donut
 {
 	struct TShape
 	{
 		std::vector<std::string> info;
 	};

 	namespace TSkyboxComponent
 	{
 		enum Type
 		{
 			PX,
 			NX,
 			PY,
 			NY,
 			PZ,
 			NZ
 		};
 	}
    std::string SkyboxComponentToString(TSkyboxComponent::Type parType)
    {
        switch(parType)
        {
            case TSkyboxComponent::PX:
                return "/px";
            case TSkyboxComponent::NX:
                return "/nx";
            case TSkyboxComponent::PY:
                return "/py";
            case TSkyboxComponent::NY:
                return "/ny";
            case TSkyboxComponent::PZ:
                return "/pz";
            case TSkyboxComponent::NZ:
                return "/nz";
        };
        return "";
    }
 	std::string ConcatFileName(const std::string& parFolderName,TSkyboxComponent::Type parType,TImgType::Type parImgType )
 	{
 		std::string filename(parFolderName);
 		filename+=SkyboxComponentToString(parType);
 		filename+=TextureHelpers::ImgTypeToString(parImgType);
 		return filename;
 	}

 	ResourceManager::ResourceManager()
 	{

 	}

 	ResourceManager::~ResourceManager()
 	{

 	}
 	TTexture* ResourceManager::LoadTexture(const std::string&  _textureName)
 	{
 		auto it = FTextures.find(_textureName);
 		if(it != FTextures.end())
 		{
 			RESOURCE_INFO(_textureName<<" already loaded");
 			it->second->FNbRef++;
 			return it->second;
 		}
 		else
 		{
 			RESOURCE_INFO("Reading "<<_textureName);
 			TTexture * texture =  TextureHelpers::LoadTexture(_textureName);
 			FTextures[_textureName] = texture;
 			TextureHelpers::CreateTexture(texture);
 			texture->FNbRef++;
 			return texture;
 		}
 	}

 	TTexture* ResourceManager::GetTexture(const std::string&  _textureName)
 	{
 		auto it = FTextures.find(_textureName);
 		if(it != FTextures.end())
 		{
 			return it->second;
 			it->second->FNbRef++;
 		}
 		return NULL;
 	}

	TSkyboxTexture* ResourceManager::LoadSkybox(const std::string&  parTextureName)
	{
		return NULL;
	}
	TSkyboxTexture* ResourceManager::LoadSkybox(const std::string&  parTextureName,TImgType::Type parType)
	{
		TSkyboxTexture * result = GetSkybox(parTextureName);
		if(!result)
		{
			TSkyboxTexture * skybox = new TSkyboxTexture(parTextureName);
			skybox->FTextures[0] =  TextureHelpers::LoadTexture(ConcatFileName(parTextureName,TSkyboxComponent::PX,parType));
			skybox->FTextures[1] =  TextureHelpers::LoadTexture(ConcatFileName(parTextureName,TSkyboxComponent::NX,parType));
			skybox->FTextures[2] =  TextureHelpers::LoadTexture(ConcatFileName(parTextureName,TSkyboxComponent::PY,parType));
			skybox->FTextures[3] =  TextureHelpers::LoadTexture(ConcatFileName(parTextureName,TSkyboxComponent::NY,parType));
			skybox->FTextures[4] =  TextureHelpers::LoadTexture(ConcatFileName(parTextureName,TSkyboxComponent::PZ,parType));
			skybox->FTextures[5] =  TextureHelpers::LoadTexture(ConcatFileName(parTextureName,TSkyboxComponent::NZ,parType));
			skybox->FID = TextureHelpers::	CreateTextureCube();
			TextureHelpers::BindToCubeMap(GL_TEXTURE_CUBE_MAP_POSITIVE_X, skybox->FTextures[0]);
			TextureHelpers::BindToCubeMap(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, skybox->FTextures[1]);
			TextureHelpers::BindToCubeMap(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, skybox->FTextures[2]);
			TextureHelpers::BindToCubeMap(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, skybox->FTextures[3]);
			TextureHelpers::BindToCubeMap(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, skybox->FTextures[4]);
			TextureHelpers::BindToCubeMap(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, skybox->FTextures[5]);
		}
		return result;
	}
	TSkyboxTexture* ResourceManager::GetSkybox(const std::string&  parTextureName)
	{

 		auto it = FSkyboxTextures.find(parTextureName);
 		if(it != FSkyboxTextures.end())
 		{
 			return it->second;
 		}
 		return NULL;
	}

	TGeometry* ResourceManager::GetGeometry(const TShader& parShader, const std::string&  parFileName)
	{
		// Looking in the databaseModel
 		auto it = FGeometries.find(parFileName);
 		if(it != FGeometries.end())
 		{
  			RESOURCE_INFO(parFileName<<" already loaded"); 
 			return it->second;
 		}
		std::string model = parFileName.substr(1,parFileName.size());
  		RESOURCE_INFO("Trying to load Wavefront: "<<model); 
		// Liste des vertices
		std::vector<Vector3> listePoints;
		// Liste des infos par point
		std::vector<Vector3> normales;
		std::vector<Vector2> uvList;

		// Gestion des infos
		std::list<TShape> shapes;
		
		fstream in;
		in.open(model.c_str(), std::fstream::in);
	  	if (!in) 
	  	{ 
	  		ASSERT_FAIL_MSG("Cannot find model obj: "<<model); 
	  		return NULL;
	  	}
		string line;
		while (getline(in, line)) 
		{
			if (line.substr(0,2) == "o ") 
			{
				while(getline(in, line) && line.substr(0,2) != "o ")
				{
		  			if (line.substr(0,2) == "v ") 
				    {
		  				// INPUT_DEBUG("Nouveau vertice.");
						stringstream s(line.substr(2));
						Vector3 v; 
						s >> v.x; 
						s >> v.y; 
						s >> v.z; 
						listePoints.push_back(v);
				    }
				    else if (line.substr(0,2)=="f ")
				    {
				    	TShape newShape;
				    	while(line.substr(0,2)=="f ")
				    	{
				    		// INPUT_DEBUG("new primitive "<< line);
				    		newShape.info.push_back(line.substr(2));
				    		if(!getline(in, line))
				    			break;
				    	}

				    	shapes.push_back(newShape);
				    }
				    else if(line[0] == 'v' && line[1] == 't') 
				    { 	
				    	// INPUT_DEBUG("UV mapping.");
						istringstream s(line.substr(2));
						float u,v;
						s >> u;
						s >> v;
						Vector2 map;
						map.x = u;
						map.y = v;
				      	uvList.push_back(map);
					}
				    else if(line[0] == 'v' && line[1] == 'n') 
				    { 
				    	//INPUT_DEBUG("Normal.");
						istringstream s(line.substr(2));
						Vector3 normal;
						s >> normal.x;
						s >> normal.y;
						s >> normal.z;
				      	normales.push_back(normal);
					}
				}
			}
		    else if (line[0] == '#') 
		    { 
		    	// Commentaire
			}
		}
	 	TGeometry * newModel = new TGeometry();
	 	GLfloat * data;
	 	unsigned int* indices;
		GLuint VAO;
		glGenVertexArrays (1, &VAO);
		glBindVertexArray (VAO);

		foreach_macro(shape,shapes)
		{
			TShape & currentShape = *shape;
			int nbShape = currentShape.info.size();
			ASSERT_MSG_NO_RELEASE(currentShape.info.size()>0, "Dans le fichier de modèle, une ligne commencant par f error");
			std::vector<std::string> sample;
			split(currentShape.info[0], ' ', sample); 
			int dimShape = sample.size();
			ASSERT_MSG_NO_RELEASE((dimShape==3 || dimShape==4), "Shape de dimension autre que 3 ou 4");
			std::vector<std::string> sample2;
			split(sample[2],'/', sample2);
			int nbInfo = sample2.size();

			if(nbInfo==1)
			{
				data = new GLfloat[3*dimShape*nbShape];
				int verticeCounter = 0;
				foreach_macro(prim, currentShape.info)
				{
					std::vector<std::string> vertices;
					split(*prim,' ', vertices);
					// vertices.erase(vertices.begin());
					foreach_macro(vertice, vertices)
					{
						Vector3& point = listePoints[stringConvert<int>(*vertice)-1];
						data[verticeCounter*3] = point.x;
						data[verticeCounter*3+1] = point.y;
						data[verticeCounter*3+2] = point.z;
						verticeCounter++;
					}	
				}
				indices = new unsigned int[verticeCounter];
				for(int i=0; i < verticeCounter;i++)
				{
					indices[i]=i;
				}
				GLuint VBO;
				GLuint IBO;
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*verticeCounter*3, data, GL_STATIC_DRAW);

				glGenBuffers(1, &IBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*verticeCounter, indices, GL_STATIC_DRAW);

				GLuint posAtt = glGetAttribLocation(parShader.FProgramID, "position");

				glEnableVertexAttribArray (posAtt);

				glVertexAttribPointer (posAtt, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				delete [] data;
				delete [] indices;
				newModel->vertexArray = VAO;
				newModel->nbVertices = verticeCounter;
			}
			else if(nbInfo==2)
			{
				data = new GLfloat[5*dimShape*nbShape];
				int verticeCounter = 0;
				foreach_macro(prim, currentShape.info)
				{
					std::vector<std::string> vertices;
					split(*prim,' ', vertices);
					ASSERT_MSG_NO_RELEASE(vertices.size()==3, *prim);
					vertices.erase(vertices.begin());
					foreach_macro(vertice, vertices)
					{
						std::vector<std::string> dataVert;
						split(*vertice,'/', dataVert);
						Vector3& point = listePoints[stringConvert<int>(dataVert[0])-1];
						data[verticeCounter*3] = point.x;
						data[verticeCounter*3+1] = point.y;
						data[verticeCounter*3+2] = point.z;

						Vector2& mapp = uvList[stringConvert<int>(dataVert[1])-1];
						data[3*dimShape*nbShape+verticeCounter*2] = mapp.x;
						data[3*dimShape*nbShape+verticeCounter*2+1] = mapp.y;
						verticeCounter++;
					}	
				}
				indices = new unsigned int[verticeCounter];
				for(int i=0; i < verticeCounter;i++)
				{
					indices[i]=i;
				}
				GLuint VBO;
				GLuint IBO;
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*verticeCounter*8, data, GL_STATIC_DRAW);

				glGenBuffers(1, &IBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*verticeCounter, indices, GL_STATIC_DRAW);

				GLuint posAtt = glGetAttribLocation(parShader.FProgramID, "position");
				GLuint texCoordAtt = glGetAttribLocation(parShader.FProgramID, "tex_coord");

				glEnableVertexAttribArray (posAtt);
				glEnableVertexAttribArray (texCoordAtt);

				glVertexAttribPointer (posAtt, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glVertexAttribPointer (texCoordAtt, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof (GLfloat)*verticeCounter*3));

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				delete [] data;
				delete [] indices;
				newModel->vertexArray = VAO;
				newModel->nbVertices = verticeCounter;
			}
			else if(nbInfo==3)
			{
				data = new GLfloat[8*dimShape*nbShape];
				int verticeCounter = 0;
				foreach_macro(prim, currentShape.info)
				{
					std::vector<std::string> vertices;
					split(*prim,' ', vertices);
					foreach_macro(vertice, vertices)
					{
						std::vector<std::string> dataVert;
						split(*vertice, '/', dataVert);
						Vector3& point = listePoints[stringConvert<int>(dataVert[0])-1];
						data[verticeCounter*3] = point.x;
						data[verticeCounter*3+1] = point.y;
						data[verticeCounter*3+2] = point.z;

						Vector2& mapp = uvList[stringConvert<int>(dataVert[1])-1];
						data[3*dimShape*nbShape+verticeCounter*2] = mapp.x;
						data[3*dimShape*nbShape+verticeCounter*2+1] = mapp.y;

						Vector3& norm = normales[stringConvert<int>(dataVert[2])-1];
						data[5*dimShape*nbShape+verticeCounter*3] = norm.x;
						data[5*dimShape*nbShape+verticeCounter*3+1] = norm.y;
						data[5*dimShape*nbShape+verticeCounter*3+2] = norm.z;

						verticeCounter++;
					}	
				}
				indices = new unsigned int[verticeCounter];
				for(int i=0; i < verticeCounter;i++)
				{
					indices[i]=i;
				}
				GLuint VBO;
				GLuint IBO;
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*verticeCounter*8, data, GL_STATIC_DRAW);

				glGenBuffers(1, &IBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*verticeCounter, indices, GL_STATIC_DRAW);

				GLuint posAtt = glGetAttribLocation(parShader.FProgramID, "position");
				GLuint normalAtt = glGetAttribLocation(parShader.FProgramID, "normal");
				GLuint texCoordAtt = glGetAttribLocation(parShader.FProgramID, "tex_coord");

				glEnableVertexAttribArray (posAtt);
				glEnableVertexAttribArray (normalAtt);
				glEnableVertexAttribArray (texCoordAtt);

				glVertexAttribPointer (posAtt, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glVertexAttribPointer (texCoordAtt, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof (GLfloat)*verticeCounter*3));
				glVertexAttribPointer (normalAtt, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof (GLfloat)*verticeCounter*5));

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				delete [] data;
				delete [] indices;
				newModel->vertexArray = VAO;
				newModel->nbVertices = verticeCounter;
			}	
		}
		glBindVertexArray (0);
		FGeometries[parFileName] = newModel;
		return newModel;
	}
	std::vector<int> ResourceManager::LoadObjToTexture(const std::string&  parFileName, std::vector<TTexture*>& parTexturetable)
	{
		// Looking in the databaseModel
		std::string model = parFileName;
  		INPUT_ERROR("Loading obj file to texture: "<<model); 
		// Liste des vertices
		std::vector<Vector3> listePoints;
		// Liste des infos par point
		std::vector<Vector3> normales;
		std::vector<Vector2> uvList;

		// Gestion des infos
		std::list<TShape> shapes;
		
		fstream in;
		in.open(model.c_str(), std::fstream::in);
	  	if (!in) 
	  	{ 
	  		ASSERT_FAIL_MSG("Cannot find model obj: "<<model); 
	  		return std::vector<int>(0);
	  	}
		string line;
		while (getline(in, line)) 
		{
			if (line.substr(0,2) == "o ") 
			{
				while(getline(in, line) && line.substr(0,2) != "o ")
				{
		  			if (line.substr(0,2) == "v ") 
				    {
		  				// INPUT_DEBUG("Nouveau vertice.");
						stringstream s(line.substr(2));
						Vector3 v; 
						s >> v.x; 
						s >> v.y; 
						s >> v.z; 
						listePoints.push_back(v);
				    }
				    else if (line.substr(0,2)=="f ")
				    {
				    	TShape newShape;
				    	while(line.substr(0,2)=="f ")
				    	{
				    		// INPUT_DEBUG("new primitive "<< line);
				    		newShape.info.push_back(line.substr(2));
				    		if(!getline(in, line))
				    			break;
				    	}
			    		// INPUT_DEBUG("Add shape");

				    	shapes.push_back(newShape);
				    }
				    else if(line[0] == 'v' && line[1] == 't') 
				    { 	
				    	// INPUT_DEBUG("UV mapping.");
						istringstream s(line.substr(2));
						float u,v;
						s >> u;
						s >> v;
						Vector2 map;
						map.x = u;
						map.y = v;
				      	uvList.push_back(map);
					}
				    else if(line[0] == 'v' && line[1] == 'n') 
				    { 
				    	//INPUT_DEBUG("Normal.");
						istringstream s(line.substr(2));
						Vector3 normal;
						s >> normal.x;
						s >> normal.y;
						s >> normal.z;
				      	normales.push_back(normal);
					}
				}
			}
		    else if (line[0] == '#') 
		    { 
		    	// Commentaire
			}
		}
		std::vector<int> nbShapes;
		foreach_macro(shape, shapes)
		{
			TShape & currentShape = *shape;
			int nbShape = currentShape.info.size();
			ASSERT_MSG_NO_RELEASE(currentShape.info.size()>0, "Dans le fichier de modèle, aucune ligne commencant par f error");
			std::vector<std::string> sample;
			split(currentShape.info[0],' ', sample); 
			int dimShape = sample.size();
			ASSERT_MSG_NO_RELEASE(dimShape==3, "Shape de dimension autre que 3 ou 4");
	  		INPUT_DEBUG("Model line: "<<currentShape.info[0]); 
			std::vector<std::string> sample2;
			split(sample[2],'/', sample2);
			int nbInfo = sample2.size();

			const int verticeSize = 9;
			const int lineSize = verticeSize*3; // (NORMAL(3)+POSITION(3)+UV(2))*NB_PTS(3)
			INPUT_DEBUG("Il y a "<<nbShape<<" points"); 
			TTexture* shapeData = new TTexture(verticeSize, nbShape);
			shapeData->FDataType = TDataType::FLOAT;
			GLfloat * data = new GLfloat[nbShape * lineSize];
			if(nbInfo == 1)
			{
				int lineNumber = 0;
				foreach_macro(prim, currentShape.info)
				{
					std::vector<std::string> vertices;
					split(*prim,' ', vertices);
					int verticeCounter = 0;
					foreach_macro(vertice, vertices)
					{
						// Vertex position
						Vector3& point = listePoints[stringConvert<int>(*vertice)-1];
						const int decalage = verticeCounter*verticeSize+ lineSize * lineNumber;
						data[decalage] = PACK_DATA(point.x, 1000000.0);
						data[1+ decalage] = PACK_DATA(point.y, 1000000.0);
						data[2+ decalage] = PACK_DATA(point.z, 1000000.0);
						// Vertex normal
						data[3+decalage] = PACK_DATA(0.0, 1000000.0);
						data[4+decalage] = PACK_DATA(0.0, 1000000.0);
						data[5+decalage] = PACK_DATA(1.0, 1000000.0);

						data[6+decalage] = PACK_DATA(0.0, 1000000.0);
						data[7+decalage] = PACK_DATA(0.0, 1000000.0);
						data[8+decalage] = PACK_DATA(0.0, 1000000.0);
						verticeCounter++;
					}
					lineNumber++;	
				}
			}
			else if (nbInfo == 2)
			{
				int lineNumber = 0;
				foreach_macro(prim, currentShape.info)
				{
					std::vector<std::string> vertices;
					split(*prim,' ', vertices);
					int verticeCounter = 0;
					foreach_macro(vertice, vertices)
					{
						// Vertex position
						std::vector<std::string> dataVert;
						split(*vertice,'/', dataVert);
						Vector3& point = listePoints[stringConvert<int>(dataVert[0])-1];
						const int decalage = verticeCounter*verticeSize+ lineSize * lineNumber;
						data[decalage] = PACK_DATA(point.x, 1000000.0);
						data[1+ decalage] = PACK_DATA(point.y, 1000000.0);
						data[2+ decalage] = PACK_DATA(point.z, 1000000.0);
						// Vertex normal
						data[3+decalage] = PACK_DATA(0.0, 1000000.0);
						data[4+decalage] = PACK_DATA(0.0, 1000000.0);
						data[5+decalage] = PACK_DATA(1.0, 1000000.0);
						Vector2& mapp = uvList[stringConvert<int>(dataVert[1])-1];
						data[6+decalage] = PACK_DATA(mapp.x, 1000000.0);
						data[7+decalage] = PACK_DATA(mapp.y, 1000000.0);
						data[8+decalage] = PACK_DATA(0.0, 1000000.0);
						verticeCounter++;
					}
					lineNumber++;	
				}
			}
			else if (nbInfo == 3)
			{
				int lineNumber = 0;
				foreach_macro(prim, currentShape.info)
				{
					std::vector<std::string> vertices;
					split(*prim,' ', vertices);
					int verticeCounter = 0;
					foreach_macro(vertice, vertices)
					{
						// Vertex position
						std::vector<std::string> dataVert;
						split(*vertice,'/', dataVert);
						Vector3& point = listePoints[stringConvert<int>(dataVert[0])-1];
						const int decalage = verticeCounter*verticeSize+ lineSize * lineNumber;
						data[decalage] = PACK_DATA(point.x, 1000000.0);
						data[1+ decalage] = PACK_DATA(point.y, 1000000.0);
						data[2+ decalage] = PACK_DATA(point.z, 1000000.0);
						// std::cout<<"decalage "<<decalage<<std::endl;
						// std::cout<<"Point "<<point.x<<" "<<point.y<<" "<<point.z<<" "<<std::endl;
						// Vertex normal
						Vector3& norm = normales[stringConvert<int>(dataVert[2])-1];
						data[3+decalage] = PACK_DATA(norm.x, 1000000.0);
						data[4+decalage] = PACK_DATA(norm.y, 1000000.0);
						data[5+decalage] = PACK_DATA(norm.z, 1000000.0);
						// std::cout<<"Normale "<<norm.x<<" "<<norm.y<<" "<<norm.z<<" "<<std::endl;

						Vector2& mapp = uvList[stringConvert<int>(dataVert[1])-1];
						data[6+decalage] = PACK_DATA(mapp.x, 1000000.0);
						data[7+decalage] = PACK_DATA(mapp.y, 1000000.0);
						data[8+decalage] = PACK_DATA(0.0, 1000000.0);
						// std::cout<<"TexCoord "<<mapp.x<<" "<<mapp.y<<std::endl;
						verticeCounter++;
					}
					// std::cout<<"ENDPRIMITIVE"<<std::endl;
					lineNumber++;	
				}
			}
			// for(int i = 0; i < nbShape * lineSize;i++)
			// {
			// 	// std::cout<<"IVAL "<<i<<" VAL: "<<data[i]<<" ";
			// 	std::cout<<data[i]<<" ";
			// }
			// std::cout<<std::endl;
			shapeData->FData = (GLvoid*)data;
			parTexturetable.push_back(shapeData);
			nbShapes.push_back(nbShape);
		}
		return nbShapes;
	}
	void ResourceManager::LoadMaterial(const TShader& parShader,  const TMaterial&  _material)
	{
		foreach_macro(uni, _material.uniforms)
		{
			switch(uni->dataType)
			{
				case TShaderData::INTEGER:
					ShaderManager::Instance().InjectInt(parShader,stringConvert<int>(uni->value), uni->name);
				break;
				case TShaderData::FLOAT:
					ShaderManager::Instance().InjectFloat(parShader, stringConvert<float>(uni->value),uni->name);
				break;
				default:
				break;
			}
		}
		foreach_macro(tex, _material.textures)
		{
			ShaderManager::Instance().InjectTex(parShader,tex->texID, tex->name,tex->offset);
		}
	}
	void ResourceManager::LoadTextures(TSugar&  parSugar)
	{
		RESOURCE_INFO("Loading textures for "<<parSugar.name)
		foreach_macro(tex,parSugar.material.textures)
		{
			TTexture* texPtr = LoadTexture(tex->file);
  			tex->texID =texPtr->FID;
		}
	}
}