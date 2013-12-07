
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
	/*
	void Camera::SetPerspective(float parAngle,)
	{
		FViewMatrix = FViewMatrix*Matrix4::rotateZAxis(parAngle);
	}
	*/
	void Camera::Roll(double parAngle)
	{
		FViewMatrix = FViewMatrix*Matrix4::rotateZAxis(parAngle);
	}

	void Camera::Yaw(double parAngle)
	{
		FViewMatrix = FViewMatrix*Matrix4::rotateYAxis(parAngle);
	}


	void Camera::Pitch(double parAngle)
	{
		FViewMatrix = FViewMatrix*Matrix4::rotateXAxis(parAngle);
	}

	void Camera::Translate(const Vector3& parDir)
	{
		FViewMatrix = FViewMatrix*Matrix4::translate(parDir);
	}
}