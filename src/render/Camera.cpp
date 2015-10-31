
#include "Camera.h"


namespace Donut 
{
	Camera::Camera()
	: FViewMatrix()
	, FProjection()
	, FHasChanged(true)
	{
		matrix4(FViewMatrix, MatrixInit::Identity);
		matrix4(FProjection, MatrixInit::Identity);
	}

	Camera::~Camera()
	{
		
	}
	void Camera::DefinePerspective(float parFovy, float parAspect, float parNear, float parFar)
	{
		AsPerspective(FProjection, parFovy,parAspect,parNear,parFar);
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}
	void Camera::Roll(double parAngle)
	{
		FViewMatrix = RotateZAxis(parAngle)*FViewMatrix;
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::Yaw(double parAngle)
	{
		FViewMatrix = RotateYAxis(parAngle)*FViewMatrix;
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::Pitch(double parAngle)
	{
		FViewMatrix = RotateXAxis(parAngle)*FViewMatrix;
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::Translate(const Vector3& parDir)
	{
		FViewMatrix = Translate_M4(parDir)*FViewMatrix;
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::ChangeNoticed()
	{
		FHasChanged.SetValue(false);
	}
}