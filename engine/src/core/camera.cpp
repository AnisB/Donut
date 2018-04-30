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
#include "core/Camera.h"

// Bento includes
#include <bento_math/matrix3.h>
#include <bento_math/matrix4.h>

// STL inlcudes
#include <math.h>

namespace donut 
{
	// Cst
	Camera::Camera()
	// Init of the matrices
	: m_viewMatrix()
	, m_viewMatrix_inverse()
	, m_projection()
	, m_projectionView()
	// projection data
	, m_near(0.1f)
	, m_far(1000.0f)
	, m_focus((m_near+m_far)/(2.0f*(m_far-m_near)))
	// View data
	, m_yaw(0.0f)
	, m_pitch(0.0f)
	, m_position()
	{
		SetIdentity(m_viewMatrix);
		bento::set_identity(m_viewMatrix_inverse);
		SetIdentity(m_projection);
		SetIdentity(m_projectionView);
	}

	Camera::~Camera()
	{
		// Nothing to do
	}

	// Define the perspective data
	void Camera::DefinePerspective(float _fovy, float _apsect, float _near, float _far)
	{
		// Setting the data
		m_near = _near;
		m_far = _far;
		m_fcoeff = 2.0f / log2(m_far + 1.0f);
		m_focus = 100.0f / (m_far - m_near);

		// Compute the perspective matrix
		AsPerspective(m_projection, _fovy, _apsect, _near, _far);
		// Update the frustum data
		m_frustum.DefineProjection(_fovy, _apsect, _near, _far);

		// Comibinig it to the viex matrix for caching purposes
		m_projectionView = m_projection * m_viewMatrix;
	}

	// Apply a yaw using a given angle
	void Camera::Yaw(float _angle)
	{
		// Incrementing the yaw angle
		m_yaw = m_yaw + _angle;
		UpdateViewData();
	}

	// Apply a pitch using a given angle
	void Camera::Pitch(float _angle)
	{
		m_pitch = m_pitch + _angle;
		UpdateViewData();
	}

	// Apply a translation
	void Camera::Translate(const bento::Vector3& _dir)
	{
		// Compute the translation in view space
		const bento::Vector3& dir = m_viewMatrix_inverse * _dir;
		// Update position
		m_position = m_position + bento::vector3(dir.x, dir.y, dir.z);
		UpdateViewData();
	}

	// Update the view data
	void Camera::UpdateViewData()
	{
		m_viewMatrix = bento::RotateXAxis(m_pitch) * bento::RotateYAxis(m_yaw) * Translate_M4(m_position);
		m_viewMatrix_inverse = Inverse3x3(m_viewMatrix);
		m_projectionView = m_projection * m_viewMatrix;
	}

	void Camera::AppendUniforms(std::map<std::string, TUniform>& _uniforms)
	{
		// Injecting view matrix
		_uniforms["view"].set_data(TShaderDataType::MAT4, "view", m_viewMatrix);
		// Injecting inversed view matrix
		_uniforms["view_inverse"].set_data(TShaderDataType::MAT3, "view_inverse", m_viewMatrix_inverse);
		// Injecting projection matrix
		_uniforms["projection"].set_data(TShaderDataType::MAT4, "projection", m_projection);
		// Injecting projection matrix
		_uniforms["viewprojection"].set_data(TShaderDataType::MAT4, "viewprojection", m_projection * m_viewMatrix);
		// Injecting zbuffer fcoef
		_uniforms["fcoef"].set_data(TShaderDataType::FLOAT, "fcoef", m_fcoeff);
		// Injecting focus distance
		_uniforms["camera_position"].set_data(TShaderDataType::VEC3, "camera_position", m_position);
		// Injecting focus distance
		_uniforms["focus"].set_data(TShaderDataType::FLOAT, "focus", m_focus);
	}
}