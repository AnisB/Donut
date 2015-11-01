/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/

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
		AsPerspective(FProjection, parFovy, parAspect, parNear, parFar);
		FProjectionView = FProjection * FViewMatrix;
		FHasChanged.SetValue(true);
	}
	void Camera::Roll(double _angle)
	{
		FViewMatrix = RotateZAxis(_angle) * FViewMatrix;
		FProjectionView = FProjection * FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::Yaw(double _angle)
	{
		FViewMatrix = RotateYAxis(_angle) * FViewMatrix;
		FProjectionView = FProjection * FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::Pitch(double _angle)
	{
		FViewMatrix = RotateXAxis(_angle) * FViewMatrix;
		FProjectionView = FProjection*FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::Translate(const Vector3& _dir)
	{
		FViewMatrix = Translate_M4(_dir) * FViewMatrix;
		FProjectionView = FProjection * FViewMatrix;
		FHasChanged.SetValue(true);
	}

	void Camera::ChangeNoticed()
	{
		FHasChanged.SetValue(false);
	}
}