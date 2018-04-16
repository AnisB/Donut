#pragma once

// Bento includes
#include <bento_math/types.h>
#include <bento_math/vector3.h>

namespace donut
{
	struct TBox3
	{
		bento::Vector3 min;
		bento::Vector3 max;
	};

	namespace box
	{
		void reset(TBox3& target_box);
		bento::Vector3 center(const TBox3& target_box);
		bento::Vector3 width(const TBox3& target_box);
		TBox3 transform(const TBox3& target_box, const bento::Matrix4& tm);
		void include_point(TBox3& target_box, const bento::Vector3& pos);
		void include_points(TBox3& target_box, const bento::Vector3* position, uint32_t num_points);
	};
}