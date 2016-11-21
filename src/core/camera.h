#ifndef CAMERA_CORE_DONUT
#define CAMERA_CORE_DONUT

// Library includes
#include "butter/types.h"
#include "core/frustum.h"
#include "graphics/uniformhandler.h"
#include "multithread/usualthreadsafeobjects.h"

// STL includes
#include <vector>
#include <map>

namespace Donut
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
			void DefinePerspective(double parFovy, double parAspect, double parNear, double parFar);

			// Fetch the the frustum data
			const TFrustum& FrusumDescriptor() { return m_frustum; }

			// Output the uniforms for rendering purposes
			void AppendUniforms(std::map<std::string, TUniformHandler>& _uniforms);

			// Fetch the camera's position
			const Vector3& Position() {return m_position;}

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
			double m_near;
			double m_far;
			double m_fcoeff;
			double m_focus;

			// View data
			double m_yaw;
			double m_pitch;
			Vector3 m_position;
	};
}


#endif //CAMERA_CORE_DONUT