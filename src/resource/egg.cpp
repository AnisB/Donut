// Library includes
#include "egg.h"

namespace donut
{

	std::ostream& operator<<(std::ostream& _os, const TEgg& _eggInstance)
	{
		_os.write((char*)&_eggInstance.nbVertices, sizeof(int));
		_os.write((char*)_eggInstance.vertsNormalsUVs, sizeof(float) * 8 * _eggInstance.nbVertices);
		_os.write((char*)&_eggInstance.nbFaces, sizeof(int));
		_os.write((char*)_eggInstance.faces, sizeof(unsigned int) * 3 * _eggInstance.nbFaces);
		return _os;
	}

	std::istream& operator >> (std::istream& _is, TEgg& _eggInstance)
	{
		// Reading the number of vertices
		_is.read((char*)&_eggInstance.nbVertices, sizeof(int));

		// Allocating the vertex normal uv memory space
		_eggInstance.vertsNormalsUVs = new float[8 * _eggInstance.nbVertices];

		// Reading them
		_is.read((char*)_eggInstance.vertsNormalsUVs, sizeof(float) * 8 * _eggInstance.nbVertices);

		// Reading the number of faces
		_is.read((char*)&_eggInstance.nbFaces, sizeof(int));

		//Allocating the faces memory space
		_eggInstance.faces = new unsigned int[3 * _eggInstance.nbFaces];

		// Reading them
		_is.read((char*)_eggInstance.faces, sizeof(unsigned int) * 3 * _eggInstance.nbFaces);

		return _is;
	}
}