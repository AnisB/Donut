
#include "Camera.h"


namespace Donut 
{
	Camera::Camera()
	: FViewMatrix(MatrixInit::Identity)
	, FProjection(MatrixInit::Identity)
	{
	}

	Camera::~Camera()
	{
		
	}
	void Camera::DefinePerspective(float parFovy, float parAspect, float parNear, float parFar)
	{
		FProjection.AsPerspective(parFovy,parAspect,parNear,parFar);
	}
	void Camera::Roll(double parAngle)
	{
		FViewMatrix = Matrix4::rotateZAxis(parAngle)*FViewMatrix;
	}

	void Camera::Yaw(double parAngle)
	{
		FViewMatrix = Matrix4::rotateYAxis(parAngle)*FViewMatrix;
	}

	void Camera::Pitch(double parAngle)
	{
		FViewMatrix = Matrix4::rotateXAxis(parAngle)*FViewMatrix;
	}

	void Camera::Translate(const Vector3& parDir)
	{
		FViewMatrix = Matrix4::translate(parDir)*FViewMatrix;
	}
}