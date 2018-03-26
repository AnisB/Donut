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
		// Reset the members to the default values
		void reset();
		bento::Vector3 center() const { return (_max + _min) / 2.0f; }
		bento::Vector3 width() const { return (_max - _min); }

		// Override the max and min values if necessary
		inline void IncludePoint(const bento::Vector3& _pos)
		{
			// Override the miniaml
			_min.x = _pos.x < _min.x ? _pos.x : _min.x;
			_min.y = _pos.y < _min.y ? _pos.y : _min.y;
			_min.z = _pos.z < _min.z ? _pos.z : _min.z;

			// Override the maximal
			_max.x = _pos.x > _max.x ? _pos.x : _max.x;
			_max.y = _pos.y > _max.y ? _pos.y : _max.y;
			_max.z = _pos.z > _max.z ? _pos.z : _max.z;
		}

		// Include a set of points using a float buffer
		void IncludePoints(float* _pointCoords, int _nbPoints);

		// Assignment operator
		void operator=(const TBox3& _targetBox) {_min = _targetBox._min; _max = _targetBox._max;}

	public:
		bento::Vector3 _min;
		bento::Vector3 _max;
	};

	// Helper functions for bounding boxes
	TBox3 transform(const TBox3& _source, const bento::Matrix4& _tm);
}