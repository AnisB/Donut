#ifndef FRUSTUM_H
#define FRUSTUM_H

// Library includes
#include "butter/types.h"

namespace donut
{
	// Foward declare
	class TBox3;

	// Enum that defined all the possible planes of the frustum 
	namespace TFrustumPlanes
	{
		enum Type
		{
			TOP,
			BOTTOM,
			LEFT,
			RIGHT,
			NEARP,
			FARP
		};
	};

	// Enum that defined all the possible points of the frustum 
	namespace TFrustumPoints
	{
		enum Type
		{
			NEAR_TOP_LEFT,
			NEAR_TOP_RIGHT,
			NEAR_BOTTOM_LEFT,
			NEAR_BOTTOM_RIGHT,

			FAR_TOP_LEFT,
			FAR_TOP_RIGHT,
			FAR_BOTTOM_LEFT,
			FAR_BOTTOM_RIGHT
		};
	};

	//
	class TFrustum 
	{
	public:
		// Cst & Dst
		TFrustum();
		~TFrustum();

	public:
		// Definition data
		void DefineProjection(float angle, float ratio, float nearD, float farD);
		bool BoxOutside(const TBox3& _box) const;
		bool PointInFrustum(const Vector3& _point) const;
		float MaxScreenPercentage(const TBox3& _box) const;

	protected:
		void ComputeInternalData();

	protected:
		// Frustum Data
			// The planes that define it
		Vector4 pl[6];
			// The points that define it
		Vector3 pts[8];
			// Original data
		float nearD, farD, ratio, angle, tang;
			// Intermediate data
		float nw, nh, fw, fh;
	};
}
#endif // FRUSTUM_H