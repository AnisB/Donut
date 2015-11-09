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

// Library includes
#include "Camera.h"

// STL inlcudes
#include <math.h>

namespace Donut 
{
	Camera::Camera()
	: FViewMatrix()
	, FProjection()
	, FHasChanged(true)
	, m_near(0.1)
	, m_far(1000.0)

	{
		matrix4(FViewMatrix, MatrixInit::Identity);
		matrix4(FProjection, MatrixInit::Identity);
	}

	Camera::~Camera()
	{
		
	}

	void Camera::DefinePerspective(double parFovy, double parAspect, double parNear, double parFar)
	{
		m_near = parNear;
		m_far = parFar;
#if __posix__
		m_fcoeff = 2.0 / log2(m_far + 1.0);
#else
		m_fcoeff = 2.0 / log(m_far + 1.0)/log(2);
#endif
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

	void Camera::AppendUniforms(std::map<std::string, TUniformHandler>& _uniforms)
	{
		// Injecting view matrix
		TUniformHandler view;
		view.SetValue(TShaderData::MAT4, "view", FViewMatrix);
		_uniforms["view"] = view;
		// Injecting projection matrix
		TUniformHandler projection;
		projection.SetValue(TShaderData::MAT4, "projection", FProjection);
		_uniforms["projection"] = projection;
		// Injecting projection matrix
		TUniformHandler viewprojection;
		viewprojection.SetValue(TShaderData::MAT4, "viewprojection", FProjection*FViewMatrix);
		_uniforms["viewprojection"] = viewprojection;
		// Injecting zbuffer fcoef
		TUniformHandler fcoef;
		fcoef.SetValue(TShaderData::FLOAT, "fcoef", m_fcoeff);
		_uniforms["fcoef"] = fcoef;
	}
}