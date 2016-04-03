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
 #include "brdfhelpers.h"
 #include "resource/Common.h"
 #include "input/Common.h"
 #include <Base/Common.h>
 #include "graphics/glfactory.h"
 #include <Tools/FileLoader.h>
 #include "Base/Macro.h"
 #include "sugarLoader.h"
 #include "pipelineloader.h"
 #include "flourloader.h"

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
 	: m_rootAssetFolder("./assets/")
 	{

 	}

 	ResourceManager::~ResourceManager()
 	{

 	}

	void ResourceManager::Init(const std::string& _assertFolder)
	{
		m_rootAssetFolder = _assertFolder + "/";
		TSugarLoader::Instance().Init();
		TPipelineLoader::Instance().Init();
		TFlourLoader::Instance().Init();
	}
 	
 	TTexture* ResourceManager::FetchTexture(const std::string&  _textureName)
 	{
 		auto it = FTextures.find(_textureName);
 		if(it != FTextures.end())
 		{
 			RESOURCE_DEBUG(_textureName<<" already loaded");
 			it->second->FNbRef++;
 			return it->second;
 		}
 		else
 		{
			RESOURCE_INFO("Reading "<<_textureName);
 			TTexture * texture =  TextureHelpers::LoadTexture(RootAssetsFolder() + _textureName);
 			FTextures[_textureName] = texture;
 			TextureHelpers::CreateTexture(texture);
 			texture->FNbRef++;
 			return texture;
 		}
 	}

 	TSkyboxTexture* ResourceManager::FetchSkybox(const std::string&  _skyboxFolder, const std::string& _extension)
 	{
 		auto it = FSkyboxTextures.find(_skyboxFolder);
 		if(it != FSkyboxTextures.end())
 		{
			RESOURCE_DEBUG(_skyboxFolder<<" already loaded");
 			it->second->FNbRef++;
 			return it->second;
 		}
 		else
 		{
 			RESOURCE_INFO("Reading "<<_skyboxFolder);
 			TSkyboxTexture * skybox =  TextureHelpers::LoadSkybox(RootAssetsFolder() + _skyboxFolder, TextureHelpers::GetImgType(_extension));
 			FSkyboxTextures[_skyboxFolder] = skybox;
 			TextureHelpers::CreateSkybox(skybox);
 			skybox->FNbRef++;
 			return skybox;
 		}
 	}

	TGGXBRDF* ResourceManager::FetchBRDF(const std::string&  _brdfFileName)
 	{
 		auto it = m_brdfs.find(_brdfFileName);
 		if(it != m_brdfs.end())
 		{
			RESOURCE_DEBUG(_brdfFileName<<" already loaded");
 			return it->second;
 		}
 		else
 		{
 			RESOURCE_INFO("Reading "<<_brdfFileName);
 			TGGXBRDF* brdf =  BRDFHelpers::LoadBRDF(RootAssetsFolder() + _brdfFileName);
 			m_brdfs[_brdfFileName] = brdf;
 			BRDFHelpers::CreateBRDF(brdf);
 			return brdf;
 		}
 	}

	TGeometryContainer* ResourceManager::ReadWavefront(const std::string& _model)
	{
  		RESOURCE_INFO("Trying to load Wavefront: "<<_model); 
		// Liste des vertices
		std::vector<Vector3> listePoints;
		// Liste des infos par point
		std::vector<Vector3> normales;
		std::vector<Vector2> uvList;

		// Gestion des infos
		std::list<TShape> shapes;
		
		fstream in;
		in.open(_model.c_str(), std::fstream::in);
	  	if (!in) 
	  	{ 
	  		ASSERT_FAIL_MSG("Cannot find _model obj: "<<_model); 
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
	 	TGeometryContainer * newModel = new TGeometryContainer();
	 	unsigned int* indices;

		foreach_macro(shape,shapes)
		{
			TShape & currentShape = *shape;
			int nbShape = (int)currentShape.info.size();
			ASSERT_MSG_NO_RELEASE(currentShape.info.size()>0, "Dans le fichier de modèle, une ligne commencant par f error");
			std::vector<std::string> sample;
			split(currentShape.info[0], ' ', sample); 
			int dimShape = (int)sample.size();
			ASSERT_MSG_NO_RELEASE((dimShape==3 || dimShape==4), "Shape de dimension autre que 3 ou 4");
			std::vector<std::string> sample2;
			split(sample[2],'/', sample2);
			int nbInfo = (int)sample2.size();

			// We only get the pos buffer from the obj
			if(nbInfo==1)
			{
				newModel->vertsNormalsUVs = new GLfloat[8*dimShape*nbShape];
				GLfloat* vertexArray = newModel->vertsNormalsUVs;
				GLfloat* normalArray = vertexArray + 3*dimShape*nbShape;
				GLfloat* texCoord = normalArray + 3*dimShape*nbShape;

				int verticeCounter = 0;
				foreach_macro(prim, currentShape.info)
				{
					std::vector<std::string> vertices;
					split(*prim,' ', vertices);
					int primSize = (int)vertices.size();
					if(vertices.size() == 3)
					{
						Vector3 points[3];
						points[0] = listePoints[convertFromString<int>(vertices[0])-1];
						points[1] = listePoints[convertFromString<int>(vertices[1])-1];
						points[2] = listePoints[convertFromString<int>(vertices[2])-1];

						const Vector3& v0 = points[1]-points[0];
						const Vector3& v1 = points[2]-points[0];
						const Vector3& normal =  normalize(crossProd(v0,v1));

						for(int i = 0; i < 3; ++i)
						{
							vertexArray[(verticeCounter+i)*3] = (GLfloat)points[i].x;
							vertexArray[(verticeCounter+i)*3+1] = (GLfloat)points[i].y;
							vertexArray[(verticeCounter+i)*3+2] = (GLfloat)points[i].z;

							normalArray[(verticeCounter+i)*3] = (GLfloat)normal.x;
							normalArray[(verticeCounter+i)*3+1] = (GLfloat)normal.y;
							normalArray[(verticeCounter+i)*3+2] = (GLfloat)normal.z;
						}
						verticeCounter += primSize;
					}
					else // 4
					{
						/*
						const Vector3& point0 = listePoints[convertFromString<int>(vertices[0]-1];
						const Vector3& point1 = listePoints[convertFromString<int>(vertices[1]-1];
						const Vector3& point2 = listePoints[convertFromString<int>(vertices[2]-1];
						const Vector3& point3 = listePoints[convertFromString<int>(vertices[3]-1];
						*/
						ASSERT_NOT_IMPLEMENTED();
					}
				}
				// Creating the IBO
				newModel->nbVertices = verticeCounter;
				newModel->faces = new unsigned int[verticeCounter];
				for(int i = 0; i < verticeCounter; i++)
				{
					newModel->faces[i] = i;
				}
				newModel->nbFaces = verticeCounter/3;
			}
			else if(nbInfo==2)
			{
				newModel->vertsNormalsUVs = new GLfloat[8*dimShape*nbShape];
				GLfloat* vertexArray = newModel->vertsNormalsUVs;
				GLfloat* normalArray = vertexArray + 3*dimShape*nbShape;
				GLfloat* texCoordArray = normalArray + 3*dimShape*nbShape;

				int verticeCounter = 0;
				foreach_macro(prim, currentShape.info)
				{
					std::vector<std::string> vertices;
					split(*prim,' ', vertices);
					int primSize = (int)vertices.size();
					if(primSize == 3)
					{
						Vector3 points[3];
						std::vector<std::string> dataVert0, dataVert1, dataVert2;
						split(vertices[0],'/', dataVert0);
						split(vertices[1],'/', dataVert1);
						split(vertices[2],'/', dataVert2);
						points[0] = listePoints[convertFromString<int>(dataVert0[0])-1];
						points[1] = listePoints[convertFromString<int>(dataVert1[0])-1];
						points[2] = listePoints[convertFromString<int>(dataVert2[0])-1];

						Vector2 texCoord[3];
						texCoord[0] = uvList[convertFromString<int>(dataVert0[1])-1];
						texCoord[1] = uvList[convertFromString<int>(dataVert1[1])-1];
						texCoord[2] = uvList[convertFromString<int>(dataVert2[1])-1];

						const Vector3& v0 = points[1]-points[0];
						const Vector3& v1 = points[2]-points[0];
						const Vector3& normal =  normalize(crossProd(v0,v1));

						for(int i = 0; i < 3; ++i)
						{
							vertexArray[(verticeCounter+i)*3] = (GLfloat)points[i].x;
							vertexArray[(verticeCounter+i)*3+1] = (GLfloat)points[i].y;
							vertexArray[(verticeCounter+i)*3+2] = (GLfloat)points[i].z;

							normalArray[(verticeCounter+i)*3] = (GLfloat)normal.x;
							normalArray[(verticeCounter+i)*3+1] = (GLfloat)normal.y;
							normalArray[(verticeCounter+i)*3+2] = (GLfloat)normal.z;

							texCoordArray[(verticeCounter+i)*2] = (GLfloat)texCoord[i].x;
							texCoordArray[(verticeCounter+i)*2+1] = (GLfloat)texCoord[i].y;
						}
						verticeCounter += primSize;
					}
					else // 4
					{
						ASSERT_NOT_IMPLEMENTED();
					}
				}
				newModel->nbVertices = verticeCounter;
				newModel->faces = new unsigned int[verticeCounter];
				for(int i = 0; i < verticeCounter; i++)
				{
					newModel->faces[i] = i;
				}
				newModel->nbFaces = verticeCounter/3;
			
			}
			else if(nbInfo==3)
			{
				newModel->vertsNormalsUVs = new GLfloat[8*dimShape*nbShape];
				GLfloat* vertexArray = newModel->vertsNormalsUVs;
				GLfloat* normalArray = vertexArray + 3*dimShape*nbShape;
				GLfloat* texCoordArray = normalArray + 3*dimShape*nbShape;

				int verticeCounter = 0;
				foreach_macro(prim, currentShape.info)
				{
					std::vector<std::string> vertices;
					split(*prim,' ', vertices);
					int primSize = (int)vertices.size();
					if(primSize == 3)
					{
						Vector3 points[3];
						std::vector<std::string> dataVert0, dataVert1, dataVert2;
						split(vertices[0],'/', dataVert0);
						split(vertices[1],'/', dataVert1);
						split(vertices[2],'/', dataVert2);
						points[0] = listePoints[convertFromString<int>(dataVert0[0])-1];
						points[1] = listePoints[convertFromString<int>(dataVert1[0])-1];
						points[2] = listePoints[convertFromString<int>(dataVert2[0])-1];

						Vector2 texCoord[3];
						texCoord[0] = uvList[convertFromString<int>(dataVert0[1])-1];
						texCoord[1] = uvList[convertFromString<int>(dataVert1[1])-1];
						texCoord[2] = uvList[convertFromString<int>(dataVert2[1])-1];

						Vector3 normals[3];
						normals[0] = normales[convertFromString<int>(dataVert0[2])-1];
						normals[1] = normales[convertFromString<int>(dataVert1[2])-1];
						normals[2] = normales[convertFromString<int>(dataVert2[2])-1];

						for(int i = 0; i < 3; ++i)
						{
							vertexArray[(verticeCounter+i)*3] = (GLfloat)points[i].x;
							vertexArray[(verticeCounter+i)*3+1] = (GLfloat)points[i].y;
							vertexArray[(verticeCounter+i)*3+2] = (GLfloat)points[i].z;

							normalArray[(verticeCounter+i)*3] = (GLfloat)normals[i].x;
							normalArray[(verticeCounter+i)*3+1] = (GLfloat)normals[i].y;
							normalArray[(verticeCounter+i)*3+2] = (GLfloat)normals[i].z;

							texCoordArray[(verticeCounter+i)*2] = (GLfloat)texCoord[i].x;
							texCoordArray[(verticeCounter+i)*2+1] = (GLfloat)texCoord[i].y;
						}
						verticeCounter += primSize;
					}
					else // 4
					{
						ASSERT_NOT_IMPLEMENTED();
					}
				}
				newModel->nbVertices = verticeCounter;
				newModel->faces = new unsigned int[verticeCounter];
				for(int i = 0; i < verticeCounter; i++)
				{
					newModel->faces[i] = i;
				}
				newModel->nbFaces = verticeCounter/3;
			}
		}
		return newModel;	
	}

	TGeometry* ResourceManager::FetchGeometry(const TShader& parShader, const std::string&  _fileName)
	{
		// Looking in the databaseModel
 		auto it = FGeometries.find(_fileName);
 		if(it != FGeometries.end())
 		{
  			RESOURCE_DEBUG(_fileName<<" already loaded"); 
 			return it->second;
 		}
		TGeometryContainer* container = ReadWavefront(RelativePath(_fileName));
		ASSERT(container != nullptr);
		TGeometry* newModel = CreateGeometry(_fileName, parShader, container->vertsNormalsUVs, container->nbVertices, container->faces, container->nbFaces);
		delete container;
		FGeometries[_fileName] = newModel;
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
			int nbShape = (int)currentShape.info.size();
			ASSERT_MSG_NO_RELEASE(currentShape.info.size()>0, "Dans le fichier de modèle, aucune ligne commencant par f error");
			std::vector<std::string> sample;
			split(currentShape.info[0],' ', sample); 
			int dimShape = (int)sample.size();
			ASSERT_MSG_NO_RELEASE(dimShape==3, "Shape de dimension autre que 3 ou 4");
	  		INPUT_DEBUG("Model line: "<<currentShape.info[0]); 
			std::vector<std::string> sample2;
			split(sample[2],'/', sample2);
			int nbInfo = (int)sample2.size();

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
						Vector3& point = listePoints[convertFromString<int>(*vertice)-1];
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
						Vector3& point = listePoints[convertFromString<int>(dataVert[0])-1];
						const int decalage = verticeCounter*verticeSize+ lineSize * lineNumber;
						data[decalage] = PACK_DATA(point.x, 1000000.0);
						data[1+ decalage] = PACK_DATA(point.y, 1000000.0);
						data[2+ decalage] = PACK_DATA(point.z, 1000000.0);
						// Vertex normal
						data[3+decalage] = PACK_DATA(0.0, 1000000.0);
						data[4+decalage] = PACK_DATA(0.0, 1000000.0);
						data[5+decalage] = PACK_DATA(1.0, 1000000.0);
						Vector2& mapp = uvList[convertFromString<int>(dataVert[1])-1];
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
						Vector3& point = listePoints[convertFromString<int>(dataVert[0])-1];
						const int decalage = verticeCounter*verticeSize+ lineSize * lineNumber;
						data[decalage] = PACK_DATA(point.x, 1000000.0);
						data[1+ decalage] = PACK_DATA(point.y, 1000000.0);
						data[2+ decalage] = PACK_DATA(point.z, 1000000.0);
						// std::cout<<"decalage "<<decalage<<std::endl;
						// std::cout<<"Point "<<point.x<<" "<<point.y<<" "<<point.z<<" "<<std::endl;
						// Vertex normal
						Vector3& norm = normales[convertFromString<int>(dataVert[2])-1];
						data[3+decalage] = PACK_DATA(norm.x, 1000000.0);
						data[4+decalage] = PACK_DATA(norm.y, 1000000.0);
						data[5+decalage] = PACK_DATA(norm.z, 1000000.0);
						// std::cout<<"Normale "<<norm.x<<" "<<norm.y<<" "<<norm.z<<" "<<std::endl;

						Vector2& mapp = uvList[convertFromString<int>(dataVert[1])-1];
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

	TGeometry* ResourceManager::CreateGeometry(const std::string& _name, const TShader& parShader, float* _dataArray, int _numVert, unsigned* _indexArray, int num_faces)
	{
		TGeometry* geo = ::Donut::CreateGeometry(parShader, _dataArray, _numVert, _indexArray, num_faces);
		FGeometries[_name] = geo;
		return geo;
	}
	void ResourceManager::BindMaterial(const TShader& _shader,  const TMaterial&  _material)
	{
		foreach_macro(uni, _material.uniforms)
		{
			uni->Inject(_shader);
		}
		foreach_macro(tex, _material.textures)
		{
			ShaderManager::Instance().InjectTex(_shader,tex->texID, tex->name,tex->offset);
		}
	}
}