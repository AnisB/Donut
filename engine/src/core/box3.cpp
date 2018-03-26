// Bento includes
#include "bento_math/vector3.h"
#include "bento_math/matrix4.h"

// Library include
#include "core/box3.h"

// External includes
#include <float.h>

namespace donut
{
	TBox3::TBox3()
	{
		reset();
	}

	TBox3::~TBox3()
	{

	}

	void TBox3::reset()
	{
		_min = bento::vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		_max = -bento::vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	TBox3 transform(const TBox3 & _inputBox, const bento::Matrix4 & _mat)
	{
		// Get the translation vector
		const bento::Vector3& translate = GetTranslate(_mat);

		// Create the output box
		TBox3 new_box;
		new_box._min = translate;
		new_box._max = translate;

		float av, bv;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				av = _mat.m[i * 4 + j] * bento::at_index(_inputBox._min, j);
				bv = _mat.m[i * 4 + j] * bento::at_index(_inputBox._max, j);

				if (av < bv)
				{
					bento::at_index(new_box._min, i) += av;
					bento::at_index(new_box._max, i) += bv;

				}
				else
				{

					bento::at_index(new_box._min, i) += bv;
					bento::at_index(new_box._max, i) += av;
				}
			}
		}
		return new_box;
	}

	void TBox3::IncludePoints(float* _pointCoords, int _nbPoints)
	{
		// For each point to include
		for (int pIdx = 0; pIdx < _nbPoints; ++pIdx)
		{
			// Include it
			float* posPtr = _pointCoords + 3 * pIdx;
			const bento::Vector3& targetPoint = bento::vector3(posPtr[0], posPtr[1], posPtr[2]);
			IncludePoint(targetPoint);
		}
	}
}