// Bento includes
#include <bento_base/security.h>

// Library include
#include "tools/GeometryConverters.h"
#include "base/stringhelper.h"
#include "base/log.h"
#include "resource/egg.h"

// Bento includes
#include <bento_math/types.h>
#include <bento_math/vector3.h>

// External includes
#include <vector>

namespace donut
{
	struct TShape
	{
		std::vector<STRING_TYPE> info;
	};

	TEgg* CreateEggFromWavefront(const STRING_TYPE& _wavefrontFIle)
	{
		PRINT_ERROR("Tools", "Trying to load Wavefront: " << _wavefrontFIle);
		// Liste des vertices
		std::vector<bento::Vector3> listePoints;
		// Liste des infos par point
		std::vector<bento::Vector3> normales;
		std::vector<bento::Vector2> uvList;

		// Gestion des infos
		std::vector<TShape> shapes;

		std::fstream in;
		in.open(_wavefrontFIle.c_str(), std::fstream::in);
		if (!in)
		{
			assert_fail_msg("Cannot find _model obj");
			return NULL;
		}
		STRING_TYPE line;
		while (getline(in, line))
		{
			if (line.substr(0, 2) == "o ")
			{
				while (getline(in, line) && line.substr(0, 2) != "o ")
				{
					if (line.substr(0, 2) == "v ")
					{
						// INPUT_DEBUG("Nouveau vertice.");
						STREAM_TYPE s(line.substr(2));
						bento::Vector3 v;
						s >> v.x;
						s >> v.y;
						s >> v.z;
						listePoints.push_back(v);
					}
					else if (line.substr(0, 2) == "f ")
					{
						TShape newShape;
						while (line.substr(0, 2) == "f ")
						{
							// INPUT_DEBUG("new primitive "<< line);
							newShape.info.push_back(line.substr(2));
							if (!getline(in, line))
								break;
						}

						shapes.push_back(newShape);
					}
					else if (line[0] == 'v' && line[1] == 't')
					{
						// INPUT_DEBUG("UV mapping.");
						std::istringstream s(line.substr(2));
						float u, v;
						s >> u;
						s >> v;
						bento::Vector2 map;
						map.x = u;
						map.y = v;
						uvList.push_back(map);
					}
					else if (line[0] == 'v' && line[1] == 'n')
					{
						//INPUT_DEBUG("Normal.");
						std::istringstream s(line.substr(2));
						bento::Vector3 normal;
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
		TEgg * newModel = new TEgg();

		for (const auto& shape : shapes)
		{
			const TShape & currentShape = shape;
			int nbShape = (int)currentShape.info.size();
			assert_msg(currentShape.info.size()>0, "Dans le fichier de modele, une ligne commencant par f error");
			std::vector<STRING_TYPE> sample;
			split(currentShape.info[0], ' ', sample);
			int dimShape = (int)sample.size();
			assert_msg((dimShape == 3 || dimShape == 4), "Shape de dimension autre que 3 ou 4");
			std::vector<STRING_TYPE> sample2;
			split(sample[2], '/', sample2);
			int nbInfo = (int)sample2.size();

			// We only get the pos buffer from the obj
			if (nbInfo == 1)
			{
				newModel->vertsNormalsUVs = new float[8 * dimShape*nbShape];
				float* vertexArray = newModel->vertsNormalsUVs;
				float* normalArray = vertexArray + 3 * dimShape*nbShape;
				float* texCoord = normalArray + 3 * dimShape*nbShape;

				int verticeCounter = 0;
				for (auto& prim : currentShape.info)
				{
					std::vector<STRING_TYPE> vertices;
					split(prim, ' ', vertices);
					int primSize = (int)vertices.size();
					if (vertices.size() == 3)
					{
						bento::Vector3 points[3];
						points[0] = listePoints[convert_from_string<int>(vertices[0]) - 1];
						points[1] = listePoints[convert_from_string<int>(vertices[1]) - 1];
						points[2] = listePoints[convert_from_string<int>(vertices[2]) - 1];

						const bento::Vector3& v0 = points[1] - points[0];
						const bento::Vector3& v1 = points[2] - points[0];
						const bento::Vector3& normal = normalize(bento::cross(v0, v1));

						for (int i = 0; i < 3; ++i)
						{
							vertexArray[(verticeCounter + i) * 3] = (float)points[i].x;
							vertexArray[(verticeCounter + i) * 3 + 1] = (float)points[i].y;
							vertexArray[(verticeCounter + i) * 3 + 2] = (float)points[i].z;

							normalArray[(verticeCounter + i) * 3] = (float)normal.x;
							normalArray[(verticeCounter + i) * 3 + 1] = (float)normal.y;
							normalArray[(verticeCounter + i) * 3 + 2] = (float)normal.z;
						}
						verticeCounter += primSize;
					}
					else // 4
					{
						/*
						const Vector3& point0 = listePoints[convert_from_string<int>(vertices[0]-1];
						const Vector3& point1 = listePoints[convert_from_string<int>(vertices[1]-1];
						const Vector3& point2 = listePoints[convert_from_string<int>(vertices[2]-1];
						const Vector3& point3 = listePoints[convert_from_string<int>(vertices[3]-1];
						*/
						assert_fail();
					}
				}
				// Creating the IBO
				newModel->nbVertices = verticeCounter;
				newModel->faces = new unsigned int[verticeCounter];
				for (int i = 0; i < verticeCounter; i++)
				{
					newModel->faces[i] = i;
				}
				newModel->nbFaces = verticeCounter / 3;
			}
			else if (nbInfo == 2)
			{
				newModel->vertsNormalsUVs = new float[8 * dimShape*nbShape];
				float* vertexArray = newModel->vertsNormalsUVs;
				float* normalArray = vertexArray + 3 * dimShape*nbShape;
				float* texCoordArray = normalArray + 3 * dimShape*nbShape;

				int verticeCounter = 0;
				for(auto& prim : currentShape.info)
				{
					std::vector<STRING_TYPE> vertices;
					split(prim, ' ', vertices);
					int primSize = (int)vertices.size();
					if (primSize == 3)
					{
						bento::Vector3 points[3];
						std::vector<STRING_TYPE> dataVert0, dataVert1, dataVert2;
						split(vertices[0], '/', dataVert0);
						split(vertices[1], '/', dataVert1);
						split(vertices[2], '/', dataVert2);
						points[0] = listePoints[convert_from_string<int>(dataVert0[0]) - 1];
						points[1] = listePoints[convert_from_string<int>(dataVert1[0]) - 1];
						points[2] = listePoints[convert_from_string<int>(dataVert2[0]) - 1];

						bento::Vector2 texCoord[3];
						texCoord[0] = uvList[convert_from_string<int>(dataVert0[1]) - 1];
						texCoord[1] = uvList[convert_from_string<int>(dataVert1[1]) - 1];
						texCoord[2] = uvList[convert_from_string<int>(dataVert2[1]) - 1];

						const bento::Vector3& v0 = points[1] - points[0];
						const bento::Vector3& v1 = points[2] - points[0];
						const bento::Vector3& normal = normalize(cross(v0, v1));

						for (int i = 0; i < 3; ++i)
						{
							vertexArray[(verticeCounter + i) * 3] = (float)points[i].x;
							vertexArray[(verticeCounter + i) * 3 + 1] = (float)points[i].y;
							vertexArray[(verticeCounter + i) * 3 + 2] = (float)points[i].z;

							normalArray[(verticeCounter + i) * 3] = (float)normal.x;
							normalArray[(verticeCounter + i) * 3 + 1] = (float)normal.y;
							normalArray[(verticeCounter + i) * 3 + 2] = (float)normal.z;

							texCoordArray[(verticeCounter + i) * 2] = (float)texCoord[i].x;
							texCoordArray[(verticeCounter + i) * 2 + 1] = (float)texCoord[i].y;
						}
						verticeCounter += primSize;
					}
					else // 4
					{
						assert_fail();
					}
				}
				newModel->nbVertices = verticeCounter;
				newModel->faces = new unsigned int[verticeCounter];
				for (int i = 0; i < verticeCounter; i++)
				{
					newModel->faces[i] = i;
				}
				newModel->nbFaces = verticeCounter / 3;

			}
			else if (nbInfo == 3)
			{
				newModel->vertsNormalsUVs = new float[8 * dimShape*nbShape];
				float* vertexArray = newModel->vertsNormalsUVs;
				float* normalArray = vertexArray + 3 * dimShape*nbShape;
				float* texCoordArray = normalArray + 3 * dimShape*nbShape;

				int verticeCounter = 0;
				for(auto& prim : currentShape.info)
				{
					std::vector<STRING_TYPE> vertices;
					split(prim, ' ', vertices);
					int primSize = (int)vertices.size();
					if (primSize == 3)
					{
						bento::Vector3 points[3];
						std::vector<STRING_TYPE> dataVert0, dataVert1, dataVert2;
						split(vertices[0], '/', dataVert0);
						split(vertices[1], '/', dataVert1);
						split(vertices[2], '/', dataVert2);
						points[0] = listePoints[convert_from_string<int>(dataVert0[0]) - 1];
						points[1] = listePoints[convert_from_string<int>(dataVert1[0]) - 1];
						points[2] = listePoints[convert_from_string<int>(dataVert2[0]) - 1];

						bento::Vector2 texCoord[3];
						texCoord[0] = uvList[convert_from_string<int>(dataVert0[1]) - 1];
						texCoord[1] = uvList[convert_from_string<int>(dataVert1[1]) - 1];
						texCoord[2] = uvList[convert_from_string<int>(dataVert2[1]) - 1];

						bento::Vector3 normals[3];
						normals[0] = normales[convert_from_string<int>(dataVert0[2]) - 1];
						normals[1] = normales[convert_from_string<int>(dataVert1[2]) - 1];
						normals[2] = normales[convert_from_string<int>(dataVert2[2]) - 1];

						for (int i = 0; i < 3; ++i)
						{
							vertexArray[(verticeCounter + i) * 3] = (float)points[i].x;
							vertexArray[(verticeCounter + i) * 3 + 1] = (float)points[i].y;
							vertexArray[(verticeCounter + i) * 3 + 2] = (float)points[i].z;

							normalArray[(verticeCounter + i) * 3] = (float)normals[i].x;
							normalArray[(verticeCounter + i) * 3 + 1] = (float)normals[i].y;
							normalArray[(verticeCounter + i) * 3 + 2] = (float)normals[i].z;

							texCoordArray[(verticeCounter + i) * 2] = (float)texCoord[i].x;
							texCoordArray[(verticeCounter + i) * 2 + 1] = (float)texCoord[i].y;
						}
						verticeCounter += primSize;
					}
					else // 4
					{
						assert_fail();
					}
				}
				newModel->nbVertices = verticeCounter;
				newModel->faces = new unsigned int[verticeCounter];
				for (int i = 0; i < verticeCounter; i++)
				{
					newModel->faces[i] = i;
				}
				newModel->nbFaces = verticeCounter / 3;
			}
		}
		return newModel;
	}

	void ExportEggFile(TEgg* eggInstance, const STRING_TYPE& _outputEggFile)
	{
		std::fstream out;
		out.open(_outputEggFile.c_str(), std::fstream::out | std::ios::binary);
		out << (*eggInstance);
		out.close();
	}

	// This file takes a wavefront (.obj) and converts it to an egg file
	void ConvertWavefrontToEgg(const STRING_TYPE& _wavefront, const STRING_TYPE& _outputEggFile)
	{
		TEgg* eggInstance = CreateEggFromWavefront(_wavefront);
		ExportEggFile(eggInstance, _outputEggFile);
	}
}