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

#ifndef CAMERA_CORE_DONUT
#define CAMERA_CORE_DONUT

// Library includes
#include "butter/matrix4.h"
#include "butter/vector3.h"
#include "multithread/usualthreadsafeobjects.h"

namespace Donut
{
	class Camera
	{
		public:
			Camera();
			~Camera();

			// Utility functions
			void Yaw(double parAngle);
			void Pitch(double parAngle);
			void Roll(double parAngle);
			void Translate(const Vector3& parDir);

			// Accessors
			const Matrix4& GetViewMatrix() const { return FViewMatrix;}
			const Matrix4& GetProjectionMatrix() const{ return FProjection;}
			const Matrix4& GetProjectionViewMatrix() const{ return FProjection;}
			// Setting the projection matrix
			void DefinePerspective(float parFovy, float parAspect, float parNear, float parFar);
			
			// Modification flags
			void ChangeNoticed();
			bool HasChanged() {return FHasChanged.GetValue();}
			
		protected:
			Matrix4 FViewMatrix;
			Matrix4 FProjection;
			Matrix4 FProjectionView;
			TThreadSafeBolean FHasChanged;
	};
}


#endif //CAMERA_CORE_DONUT