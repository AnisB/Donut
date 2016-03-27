#include "brdfhelpers.h"

#include <stdio.h>

namespace Donut
{
	namespace BRDFHelpers
	{
		TGGXBRDF* LoadBRDF(const std::string& _filename)
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
			int numValues =  newBrdf->dimension[0] * newBrdf->dimension[1] * newBrdf->dimension[2];
			newBrdf->data = new double[numValues];
			fread(newBrdf->data, sizeof(double), 3 * numValues, brdf_file);
			fclose(brdf_file);
			return newBrdf;
		}

		void CreateBRDF(TGGXBRDF* _brdf)
		{
	        RESOURCE_INFO("Creating BRDF 1D texture.");
			int numValues =  _brdf->dimension[0] * _brdf->dimension[1] * _brdf->dimension[2];
	        glGenTextures(1, &(_brdf->m_id));
	        glBindTexture(GL_TEXTURE_1D, _brdf->m_id);
	        glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, numValues, 0, GL_RGB, GL_DOUBLE, _brdf->data);
	        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	        glBindTexture(GL_TEXTURE_1D, 0);
		}
	}
}