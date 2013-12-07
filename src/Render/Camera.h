#ifndef CAMERA_DONUT
#define CAMERA_DONUT

#include <Math/Matrix4.h>
#include <Math/Vector3.h>

namespace Donut
{
	class Camera
	{
		public:
			Camera();
			~Camera();

			// Rotations
			void Yaw(double parAngle);
			void Pitch(double parAngle);
			void Roll(double parAngle);
			// Translation
			void Translate(const Vector3& parDir);
			
		protected:
			Matrix4 FViewMatrix;
			Matrix4 FProjection;
	};
}
#endif //CAMERA_DONUT