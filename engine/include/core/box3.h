#pragma once

// Bento includes
#include <bento_math/types.h>
#include <bento_math/vector3.h>

namespace donut
{
	class TBox3
	{
	public:
		// Cst and Dst
		TBox3();
		~TBox3();

	public:
		void Reset();
		bento::Vector3 Center() const { return (max + min) / 2.0f; }
		bento::Vector3 Width() const { return (max - min); }

		// Override the max and min values if necessary
		inline void IncludePoint(const bento::Vector3& _pos)
		{
			// Override the miniaml
			min.x = _pos.x < min.x ? _pos.x : min.x;
			min.y = _pos.y < min.y ? _pos.y : min.y;
			min.z = _pos.z < min.z ? _pos.z : min.z;

			// Override the maximal
			max.x = _pos.x > max.x ? _pos.x : max.x;
			max.y = _pos.y > max.y ? _pos.y : max.y;
			max.z = _pos.z > max.z ? _pos.z : max.z;
		}

		// Include a set of points using a float buffer
		void IncludePoints(float* _pointCoords, int _nbPoints);

		void operator=(const TBox3& _targetBox) {min = _targetBox.min; max = _targetBox.max;}

	public:
		bento::Vector3 min;
		bento::Vector3 max;
	};

	// Helper functions for bounding boxes
	TBox3 transform(const TBox3& _source, const bento::Matrix4& _tm);
}