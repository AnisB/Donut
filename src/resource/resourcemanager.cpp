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
 #include <Math/vec.h>
 #include <Base/Common.h>
 #include <Base/DebugPrinters.h>
 #include <Render/Helper.h>
 #include <Tools/FileLoader.h>

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

 			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->FWidth, texture->FHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->FData);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_PRIORITY, 1.0); 

 			glBindTexture(GL_TEXTURE_2D, 0);
 			return texture;
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

	TModel* ResourceManager::LoadObj(const TShader& parShader, const std::string&  parFileName)
	{
		std::string model = parFileName.substr(1,parFileName.size());
  		INPUT_ERR("I will try to load: "<<model); 
		// Liste des vertices
		std::vector<TVec3> listePoints;
		// Liste des infos par point
		std::vector<TVec3> normales;
		std::vector<TVec2> uvList;

		// Gestion des infos
		std::list<TShape> shapes;
		
		fstream in;
		in.open(model.c_str(), std::fstream::in);
	  	if (!in) 
	  	{ 
	  		INPUT_DEBUG("Cannot find model obj: "<<model); 
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
		  				//INPUT_DEBUG("Nouveau vertice.");
						stringstream s(line.substr(2));
						TVec3 v; 
						s >> v.val[0]; 
						s >> v.val[1]; 
						s >> v.val[2]; 
						listePoints.push_back(v);
				    }
				    else if (line.substr(0,7) == "usemtl ") 
				    {
				    	getline(in, line);
				    	while(line.substr(0,2)!="f " && getline(in, line))
				    	{

				    	}
				    	TShape newShape;
				    	while(line.substr(0,2)=="f ")
				    	{
				    		newShape.info.push_back(line.substr(2));
				    		if(!getline(in, line))
				    			break;
				    	}
				    	shapes.push_back(newShape);
				    }
				    else if(line[0] == 'v' && line[1] == 't') 
				    { 	
				    	//INPUT_DEBUG("UV mapping.");
						istringstream s(line.substr(2));
						float u,v;
						s >> u;
						s >> v;
						TVec2 map;
						map.val[0] = u;
						map.val[1] = v;
				      	uvList.push_back(map);
					}
				    else if(line[0] == 'v' && line[1] == 'n') 
				    { 
				    	//INPUT_DEBUG("Normal.");
						istringstream s(line.substr(2));
						TVec3 normal;
						s >> normal.val[0];
						s >> normal.val[1];
						s >> normal.val[2];
				      	normales.push_back(normal);
					}
				}
			}
		    else if (line[0] == '#') 
		    { 
		    	// Commentaire
			}
		}
	 	TModel * newModel = new TModel();
	 	newModel->name = parFileName;
	 	GLfloat * data;
	 	unsigned int* indices;
		GLuint VAO;
		glGenVertexArrays (1, &VAO);
		glBindVertexArray (VAO);

		foreach(shape,shapes)
		{
			TShape & currentShape = *shape;
			int nbShape = currentShape.info.size();
			AssertNoReleasePrint(currentShape.info.size()>0, "Dans le fichier de modèle, une ligne commencant par f error");
			std::vector<std::string> sample = split(currentShape.info[0],' '); 
			int dimShape = sample.size();
			AssertNoReleasePrint((dimShape==3 || dimShape==4), "Shape de dimension autre que 3 ou 4, la dimension est:"<<dimShape);
			std::vector<std::string> sample2 = split(sample[2],'/');
			int nbInfo = sample2.size();
			if(nbInfo==1)
			{
				data = new GLfloat[3*dimShape*nbShape];
				int verticeCounter = 0;
				foreach(prim, currentShape.info)
				{
					std::vector<std::string> vertices = split(*prim,' ');
					vertices.erase(vertices.begin());
					foreach(vertice, vertices)
					{
						TVec3& point = listePoints[convertToInt(*vertice)-1];
						data[verticeCounter*3] = point.val[0];
						data[verticeCounter*3+1] = point.val[1];
						data[verticeCounter*3+2] = point.val[2];
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
				foreach(prim, currentShape.info)
				{
					std::vector<std::string> vertices = split(*prim,' ');
					vertices.erase(vertices.begin());
					foreach(vertice, vertices)
					{
						std::vector<std::string> dataVert = split(*vertice,'/');
						TVec3& point = listePoints[convertToInt(dataVert[0])-1];
						data[verticeCounter*3] = point.val[0];
						data[verticeCounter*3+1] = point.val[1];
						data[verticeCounter*3+2] = point.val[2];

						TVec2& mapp = uvList[convertToInt(dataVert[1])-1];
						data[3*dimShape*nbShape+verticeCounter*2] = mapp.val[0];
						data[3*dimShape*nbShape+verticeCounter*2+1] = mapp.val[1];

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
				foreach(prim, currentShape.info)
				{
					std::vector<std::string> vertices = split(*prim,' ');
					foreach(vertice, vertices)
					{
						std::vector<std::string> dataVert = split(*vertice,'/');
						TVec3& point = listePoints[convertToInt(dataVert[0])-1];
						data[verticeCounter*3] = point.val[0];
						data[verticeCounter*3+1] = point.val[1];
						data[verticeCounter*3+2] = point.val[2];

						TVec2& mapp = uvList[convertToInt(dataVert[1])-1];
						data[3*dimShape*nbShape+verticeCounter*2] = mapp.val[0];
						data[3*dimShape*nbShape+verticeCounter*2+1] = mapp.val[1];

						TVec3& norm = normales[convertToInt(dataVert[2])-1];
						data[5*dimShape*nbShape+verticeCounter*3] = norm.val[0];
						data[5*dimShape*nbShape+verticeCounter*3+1] = norm.val[1];
						data[5*dimShape*nbShape+verticeCounter*3+2] = norm.val[2];

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
		return newModel;
	}
	void ResourceManager::LoadSugarData(const TShader& parShader,  TSugar&  parSugar)
	{
		INPUT_DEBUG("Data "<<parSugar.uniforms.size()<<" "<<parSugar.textures.size()); 
		foreach(uni,parSugar.uniforms)
		{
			switch(uni->dataType)
			{
				case ShaderDataType::INTEGER:
					ShaderManager::Instance().InjectInt(parShader,convertToInt(uni->value), uni->name);
				break;
				case ShaderDataType::FLOAT:
					ShaderManager::Instance().InjectInt(parShader, convertToFloat(uni->value),uni->name);
				break;
				default:
				break;
			}
		}
		foreach(tex,parSugar.textures)
		{
			TTexture* texPtr = LoadTexture(tex->file);
  			INPUT_DEBUG((texPtr->FID)<<" "<<(tex->name)<<" "<<(tex->index));
  			tex->texID =texPtr->FID;
			ShaderManager::Instance().InjectTex(parShader,texPtr->FID, tex->name,tex->index);
		}
	}
}