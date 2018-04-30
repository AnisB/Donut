#pragma once

// Internal includes
#include <gpu_backend/gpu_backend.h>

// STL includes
#include <vector>

namespace donut
{
	// Class
	class TSphericalHarmonics
	{
	public:
		TSphericalHarmonics();
		~TSphericalHarmonics();
		void SetCoeffs(const float* _redCoeffs, const float* _greenCoeffs, const float* _blueCoeffs);

		void InjectData(ShaderPipelineObject _shader);
	protected:
		std::vector<float> m_red;
		std::vector<float> m_green;
		std::vector<float> m_blue;
		size_t m_degree;
	};
}