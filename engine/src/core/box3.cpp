// Bento includes
#include "bento_math/vector3.h"
#include "bento_math/matrix4.h"

// Library include
#include "core/box3.h"

// External includes
#include <float.h>

namespace donut {
namespace box {

	void reset(TBox3& target_box)
	{
		target_box.min = bento::vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		target_box.max = -bento::vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	bento::Vector3 center(const TBox3& target_box)
	{
		return (target_box.max + target_box.min) / 2.0f;
	}

	bento::Vector3 width(const TBox3& target_box)
	{
		return (target_box.max - target_box.min);
	}

	void include_point(TBox3& target_box, const bento::Vector3& position)
	{
		target_box.min.x = position.x < target_box.min.x ? position.x : target_box.min.x;
		target_box.min.y = position.y < target_box.min.y ? position.y : target_box.min.y;
		target_box.min.z = position.z < target_box.min.z ? position.z : target_box.min.z;

		target_box.max.x = position.x > target_box.max.x ? position.x : target_box.max.x;
		target_box.max.y = position.y > target_box.max.y ? position.y : target_box.max.y;
		target_box.max.z = position.z > target_box.max.z ? position.z : target_box.max.z;
	}

	void include_points(TBox3& target_box, const bento::Vector3* position, uint32_t num_points)
	{
		// For each point to include
		for (uint32_t p_idx = 0; p_idx < num_points; ++p_idx)
		{
			// Include it
			const bento::Vector3& target_point = position[p_idx];
			include_point(target_box, target_point);
		}
	}

	TBox3 transform(const TBox3 & target_box, const bento::Matrix4 & _mat)
	{
		// Get the translation vector
		const bento::Vector3& translate = GetTranslate(_mat);

		// Create the output box
		TBox3 new_box;
		new_box.min = translate;
		new_box.max = translate;

		float av, bv;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				av = _mat.m[i * 4 + j] * bento::at_index(target_box.min, j);
				bv = _mat.m[i * 4 + j] * bento::at_index(target_box.max, j);

				if (av < bv)
				{
					bento::at_index(new_box.min, i) += av;
					bento::at_index(new_box.max, i) += bv;

				}
				else
				{

					bento::at_index(new_box.min, i) += bv;
					bento::at_index(new_box.max, i) += av;
				}
			}
		}
		return new_box;
	}
}
}