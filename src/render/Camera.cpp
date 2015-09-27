
#include "Camera.h"


namespace Donut 
{
	Camera::Camera()
	: FViewMatrix(MatrixInit::Identity)
	, FProjection(MatrixInit::Identity)
	, FHasChanged(true)
	{
	}

	Camera::~Camera()
	{
		
	}
	void Camera::DefinePerspective(float parFovy, float parAspect, float parNear, float parFar)
	{
		FProjection.AsPerspective(parFovy,parAspect,parNear,parFar);
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}
	void Camera::Roll(double parAngle)
	{
		FViewMatrix = Matrix4::rotateZAxis(parAngle)*FViewMatrix;
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::Yaw(double parAngle)
	{
		FViewMatrix = Matrix4::rotateYAxis(parAngle)*FViewMatrix;
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::Pitch(double parAngle)
	{
		FViewMatrix = Matrix4::rotateXAxis(parAngle)*FViewMatrix;
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::Translate(const Vector3& parDir)
	{
		FViewMatrix = Matrix4::translate(parDir)*FViewMatrix;
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::ChangeNoticed()
	{
		FHasChanged.SetValue(false);
	}
}