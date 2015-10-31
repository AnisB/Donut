#ifndef CAMERA_DONUT
#define CAMERA_DONUT

#include <butter/Matrix4.h>
#include <butter/Vector3.h>
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

			const Matrix4& GetViewMatrix() const{ return FViewMatrix;}
			const Matrix4& GetProjectionMatrix() const{ return FProjection;}
			const Matrix4& GetProjectionViewMatrix() const{ return FProjection;}

			void DefinePerspective(float parFovy, float parAspect, float parNear, float parFar);
			void ChangeNoticed();
			bool HasChanged() {return FHasChanged.GetValue();}

			
		protected:
			Matrix4 FViewMatrix;
			Matrix4 FProjection;
			Matrix4 FProjectionView;
			TThreadSafeBolean FHasChanged;
	};
}
#endif //CAMERA_DONUT