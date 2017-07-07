#ifndef CAMERA_CORE_DONUT
#define CAMERA_CORE_DONUT

// Library includes
#include "butter/types.h"
#include "core/frustum.h"
#include "graphics/uniformhandler.h"

// STL includes
#include <vector>
#include <map>

namespace donut
{
	// This class is the camera structure of the engine, it makes available the usual operations (yaw, pitch, translate) and access to the rendering data
	class Camera
	{
		public:
			// Cst and Dst
			Camera();
			~Camera();

			// Transform data
				// Apply a yaw using a given angle
			void Yaw(double parAngle);
				// Apply a pitch using a given angle
			void Pitch(double parAngle);
				// Apply a translation
			void Translate(const Vector3& parDir);

			// Accessors
			const Matrix4& GetViewMatrix() const { return m_viewMatrix;}
			const Matrix3& GetInverseViewMatrix() const { return m_viewMatrix_inverse;}
			const Matrix4& GetProjectionMatrix() const{ return m_projection;}
			const Matrix4& GetProjectionViewMatrix() const{ return m_projectionView;}

			// Setting the projection data
			void DefinePerspective(float parFovy, float parAspect, float parNear, float parFar);

			// Fetch the the frustum data
			const TFrustum& FrusumDescriptor() { return m_frustum; }

			// Output the uniforms for rendering purposes
			void AppendUniforms(std::map<STRING_TYPE, TUniformHandler>& _uniforms);

			// Fetch the camera's position
			const Vector3& Position() {return m_position;}
			float NearPlane() {return m_near;}

	protected:
			// Compute view matrix
			void UpdateViewData();
		protected:
			// Rendering data
			Matrix4 m_viewMatrix;
			Matrix3 m_viewMatrix_inverse;
			Matrix4 m_projection;
			Matrix4 m_projectionView;
			TFrustum m_frustum;

			// Projection Data
			float m_near;
			float m_far;
			float m_fcoeff;
			float m_focus;

			// View data
			float m_yaw;
			float m_pitch;
			Vector3 m_position;
	};
}


#endif //CAMERA_CORE_DONUT