#ifndef CAMERA_DONUT
#define CAMERA_DONUT

#include <Math/Matrix4.h>
#include <Math/Vector3.h>
#include <MultiThread/UsualThreadSafeObjects.h>

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

			const Matrix4& GetViewMatrix() { return FViewMatrix;}
			const Matrix4& GetProjectionMatrix() { return FProjection;}

			void DefinePerspective(float parFovy, float parAspect, float parNear, float parFar);
			void ChangeNoticed();
			bool HasChanged() {return FHasChanged.GetValue();}

			
		protected:
			Matrix4 FViewMatrix;
			Matrix4 FProjection;
			TThreadSafeBolean FHasChanged;
	};
}
#endif //CAMERA_DONUT