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


 #ifndef DONUT_ANIMATION_ENGINE
 #define DONUT_ANIMATION_ENGINE

 #include <MultiThread/ThreadSharedObject.h>
 #include <Render/DrawableObject.h>
 #include <string>
namespace Donut 
{
	class TAnimationEngine : public TThreadSharedObject,
                          public TDrawableObject
	{
		public:
			TAnimationEngine(const std::string& parAnimationDescriptor);
			~TAnimationEngine();

 };
}
 #endif // DONUT_ANIMATION_ENGINE