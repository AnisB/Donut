// Library include
#include "core/box3.h"
#include "butter/vector3.h"
#include "butter/matrix4.h"
#include "base/security.h"

// External includes
#include <float.h>

namespace donut
{
	TBox3::TBox3()
	{
		Reset();
	}

	TBox3::~TBox3()
	{

	}

	void TBox3::Reset()
	{
		min = vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		max = -vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	TBox3 transform(const TBox3 & _inputBox, const Matrix4 & _mat)
	{
		// Get the translation vector
		const Vector3& translate = GetTranslate(_mat);

		// Create the output box
		TBox3 new_box;
		new_box.min = translate;
		new_box.max = translate;

		float av, bv;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				av = _mat.m[i * 4 + j] * atIndex_Cst(_inputBox.min, j);
				bv = _mat.m[i * 4 + j] * atIndex_Cst(_inputBox.max, j);

				if (av < bv)
				{
					atIndex(new_box.min, i) += av;
					atIndex(new_box.max, i) += bv;

				}
				else
				{

					atIndex(new_box.min, i) += bv;
					atIndex(new_box.max, i) += av;
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
			const Vector3& targetPoint = vector3(posPtr[0], posPtr[1], posPtr[2]);
			IncludePoint(targetPoint);
		}
	}
}