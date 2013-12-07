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


 #ifndef DONUT_ANIMATION
 #define DONUT_ANIMATION

 #include <Render/Defines.h>
 #include <Render/DrawableObject.h>

 #include <string>
 #include <vector>
 namespace Donut
 {

 	class TAnimation : public TDrawableObject
 	{
 	public:
 		TAnimation(unsigned parId, const std::vector<std::string> & parSprites, float parDelay, bool parLooping);
 		~TAnimation();

 	private:
 		unsigned FId;
 		std::vector<std::string> FSpritePaths;
 		float FDelay;
 		bool FLooping;

 		bool FIsFinished;

 	};
 }
 #endif // DONUT_ANIMATION