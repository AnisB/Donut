#include "brdfhelpers.h"
#include "graphics/glfactory.h"

#include <stdio.h>

namespace donut
{
	namespace BRDFHelpers
	{
		TGGXBRDF* LoadBRDF(const STRING_TYPE& _filename)
		{
			// Opening the ggx brdf fle
			FILE* brdf_file = fopen(_filename.c_str(), "rb");
			// Check that everything is fine
			ASSERT_MSG(brdf_file, "Failed to open file "<<brdf_file);
			// Creating the container
			TGGXBRDF* newBrdf = new TGGXBRDF();
			// Fetch the dimensions
			fread(newBrdf->dimension, sizeof(int), 3, brdf_file);
			RESOURCE_DEBUG("Opening BRDF file "<<_filename<<" dimensions "<< newBrdf->dimension[0]<<" "<<newBrdf->dimension[1]<<" "<<newBrdf->dimension[2]);
			int numValues =  3 * newBrdf->dimension[0] * newBrdf->dimension[1] * newBrdf->dimension[2];
			double* readBuffer = new double[numValues];
			fread(readBuffer, sizeof(double), numValues, brdf_file);
			fclose(brdf_file);
			newBrdf->data = new float[numValues];
			#pragma omp parallel for
			for (int i = 0; i < numValues; ++i)
			{
				newBrdf->data[i] = (float)(readBuffer[i]);
			}
			delete[] readBuffer;
			return newBrdf;
		}

		void CreateBRDF(TGGXBRDF* _brdf)
		{
			GL_API_CHECK_START();

	        RESOURCE_INFO("Creating BRDF 1D texture.");
	        glGenTextures(1, &(_brdf->id));
			glBindTexture(GL_TEXTURE_3D, _brdf->id);
			glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, _brdf->dimension[0], _brdf->dimension[1], _brdf->dimension[2], 0, GL_RGB, GL_FLOAT, _brdf->data);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glBindTexture(GL_TEXTURE_1D, 0);

			GL_API_CHECK_END();
		}
	}
}