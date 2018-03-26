// Library include
#include "core/frustum.h"
#include "core/box3.h"

// Bento includes
#include <bento_math/vector3.h>
#include <bento_math/vector4.h>

// External includes
#include <algorithm>

#undef max
#undef min

namespace donut
{
	// Build a plane's data from 3 points
	bento::Vector4 BuildPlane(const bento::Vector3& _a, const bento::Vector3& _b, const bento::Vector3& _c)
	{
		bento::Vector4 planeData;

		// Compute the plane's normal
		bento::Vector3 planeNormal = normalize(bento::cross(_b - _a, _c - _a));

		// Set the data
		planeData.x = planeNormal.x;
		planeData.y = planeNormal.y;
		planeData.z = planeNormal.z;
		planeData.w = -bento::dot(_a, planeNormal);

		// Return the plane
		return planeData;
	}

	// Fetch the normal from the plane data
	const bento::Vector3& Normal(const bento::Vector4& _planeData)
	{
		return *reinterpret_cast<const bento::Vector3*>(&_planeData.x);
	}

	// Cst
	TFrustum::TFrustum()
	{
	}

	// Dst
	TFrustum::~TFrustum()
	{
	}

	void TFrustum::DefineProjection(float _angle, float _ratio, float _nearD, float _farD)
	{
		// Store the initial information
		ratio = _ratio;
		angle = _angle;
		nearD = _nearD;
		farD = _farD;

		// compute width and height of the near and far plane sections
		tang = (float)tan(angle * 3.14 / 360.0);
		nh = nearD * tang;
		nw = nh * ratio;
		fh = farD  * tang;
		fw = fh * ratio;

		// Compute the internal data
		ComputeInternalData();
	}

	void TFrustum::ComputeInternalData()
	{
		bento::Vector3 near_center, far_center;

		// compute the centers of the near and far planes
		near_center = bento::v3_ZERO - bento::v3_Z * nearD;
		far_center = bento::v3_ZERO - bento::v3_Z * farD;

		// compute the 4 corners of the frustum on the near plane
		pts[TFrustumPoints::NEAR_TOP_LEFT] = near_center + bento::v3_Y * nh - bento::v3_X * nw;
		pts[TFrustumPoints::NEAR_TOP_RIGHT] = near_center + bento::v3_Y * nh + bento::v3_X * nw;
		pts[TFrustumPoints::NEAR_BOTTOM_LEFT] = near_center - bento::v3_Y * nh - bento::v3_X * nw;
		pts[TFrustumPoints::NEAR_BOTTOM_RIGHT] = near_center - bento::v3_Y * nh + bento::v3_X * nw;

		// compute the 4 corners of the frustum on the far plane
		pts[TFrustumPoints::FAR_TOP_LEFT] = far_center + bento::v3_Y * fh - bento::v3_X * fw;
		pts[TFrustumPoints::FAR_TOP_RIGHT] = far_center + bento::v3_Y * fh + bento::v3_X * fw;
		pts[TFrustumPoints::FAR_BOTTOM_LEFT] = far_center - bento::v3_Y * fh - bento::v3_X * fw;
		pts[TFrustumPoints::FAR_BOTTOM_RIGHT] = far_center - bento::v3_Y * fh + bento::v3_X * fw;

		// Compute the planes
		pl[TFrustumPlanes::TOP] = BuildPlane(pts[TFrustumPoints::NEAR_TOP_RIGHT], pts[TFrustumPoints::NEAR_TOP_LEFT], pts[TFrustumPoints::FAR_TOP_LEFT]);
		pl[TFrustumPlanes::BOTTOM] = BuildPlane(pts[TFrustumPoints::NEAR_BOTTOM_LEFT], pts[TFrustumPoints::NEAR_BOTTOM_RIGHT], pts[TFrustumPoints::FAR_BOTTOM_RIGHT]);
		pl[TFrustumPlanes::LEFT] = BuildPlane(pts[TFrustumPoints::NEAR_TOP_LEFT], pts[TFrustumPoints::NEAR_BOTTOM_LEFT], pts[TFrustumPoints::FAR_BOTTOM_LEFT]);
		pl[TFrustumPlanes::RIGHT] = BuildPlane(pts[TFrustumPoints::NEAR_BOTTOM_RIGHT], pts[TFrustumPoints::NEAR_TOP_RIGHT], pts[TFrustumPoints::FAR_BOTTOM_RIGHT]);
		pl[TFrustumPlanes::NEARP] = BuildPlane(pts[TFrustumPoints::NEAR_TOP_LEFT], pts[TFrustumPoints::NEAR_TOP_RIGHT], pts[TFrustumPoints::NEAR_BOTTOM_RIGHT]);
		pl[TFrustumPlanes::FARP] = BuildPlane(pts[TFrustumPoints::FAR_TOP_RIGHT], pts[TFrustumPoints::FAR_TOP_LEFT], pts[TFrustumPoints::FAR_BOTTOM_LEFT]);
	}

	// A point is inside if it is on the positive side of all the planes
	bool TFrustum::PointInFrustum(const bento::Vector3& _point) const
	{
		// Check each plane
		for (int i = 0; i < 6; ++i)
		{
			bool positive = (bento::dot(Normal(pl[i]), _point) + pl[i].w) > 0.0;
			if (!positive)
			{
				return false;
			}
		}
		return true;
	}

	bool TFrustum::BoxOutside(const TBox3& _box) const
	{
		// First of all check if one of the planes eliminates the box
		for (int i = 0; i<6; i++)
		{
			int out = 0;
			out += ((bento::dot(pl[i], bento::vector4(_box._min.x, _box._min.y, _box._min.z, 1.0f)) < 0.0) ? 1 : 0);
			out += ((bento::dot(pl[i], bento::vector4(_box._max.x, _box._min.y, _box._min.z, 1.0f)) < 0.0) ? 1 : 0);
			out += ((bento::dot(pl[i], bento::vector4(_box._min.x, _box._max.y, _box._min.z, 1.0f)) < 0.0) ? 1 : 0);
			out += ((bento::dot(pl[i], bento::vector4(_box._max.x, _box._max.y, _box._min.z, 1.0f)) < 0.0) ? 1 : 0);
			out += ((bento::dot(pl[i], bento::vector4(_box._min.x, _box._min.y, _box._max.z, 1.0f)) < 0.0) ? 1 : 0);
			out += ((bento::dot(pl[i], bento::vector4(_box._max.x, _box._min.y, _box._max.z, 1.0f)) < 0.0) ? 1 : 0);
			out += ((bento::dot(pl[i], bento::vector4(_box._min.x, _box._max.y, _box._max.z, 1.0f)) < 0.0) ? 1 : 0);
			out += ((bento::dot(pl[i], bento::vector4(_box._max.x, _box._max.y, _box._max.z, 1.0f)) < 0.0) ? 1 : 0);
			if (out == 8) return true;
		}

		// Secondly, check the intersection behind
		int out;
		out = 0; for (int i = 0; i<8; i++) out += ((pts[i].x > _box._max.x) ? 1 : 0); if (out == 8) return true;
		out = 0; for (int i = 0; i<8; i++) out += ((pts[i].x < _box._min.x) ? 1 : 0); if (out == 8) return true;
		out = 0; for (int i = 0; i<8; i++) out += ((pts[i].y > _box._max.y) ? 1 : 0); if (out == 8) return true;
		out = 0; for (int i = 0; i<8; i++) out += ((pts[i].y < _box._min.y) ? 1 : 0); if (out == 8) return true;
		out = 0; for (int i = 0; i<8; i++) out += ((pts[i].z > _box._max.z) ? 1 : 0); if (out == 8) return true;
		out = 0; for (int i = 0; i<8; i++) out += ((pts[i].z < _box._min.z) ? 1 : 0); if (out == 8) return true;

		// OK we have an intersection here
		return false;
	}

	float TFrustum::MaxScreenPercentage(const TBox3& _box) const
	{
		// Fetche the dimension of the box
		bento::Vector3 dimension = _box.width();

		// Fetch the maximal box dimension
		float maxBoxDimension = std::max(dimension.x, dimension.y);

		// Fetch the minimal far screen dimension
		float minScreenDimension = std::min(tang * -_box._min.z * 2, tang * -_box._min.z * ratio * 2);

		// return the percentage
		return maxBoxDimension / minScreenDimension;
	}
}