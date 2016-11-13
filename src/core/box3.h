#ifndef BOX3_CORE_H
#define BOX3_CORE_H

// Library includes
#include "butter/types.h"
#include "butter/vector3.h"

namespace Donut
{
	class TBox3
	{
	public:
		// Cst and Dst
		TBox3();
		~TBox3();

		// Manipulation method
		void Reset();

		// Override the max and min values if necessary
		inline void IncludePoint(const Vector3& _pos)
		{
			// Override the miniaml
			min.x = _pos.x < min.x ? _pos.x : min.x;
			min.y = _pos.y < min.y ? _pos.x : min.y;
			min.z = _pos.z < min.z ? _pos.x : min.z;

			// Override the maximal
			max.x = _pos.x > max.x ? _pos.x : max.x;
			max.y = _pos.y > max.y ? _pos.y : max.y;
			max.z = _pos.z > max.z ? _pos.z : max.z;
		}

		void IncludePoints(float* _pointCoords, int _nbPoints, int _shift)
		{
			// For each point to include
			for (int pIdx = 0; pIdx < _nbPoints; ++pIdx)
			{
				// Include it
				float* posPtr = _pointCoords + _shift * pIdx;
				IncludePoint(vector3(posPtr[0], posPtr[1], posPtr[2]));
			}
		}
	public:
		Vector3 min;
		Vector3 max;
	};
}

#endif // BOX3_CORE_H