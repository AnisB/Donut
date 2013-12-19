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



#ifndef DONUT_DEFINES_RENDER
#define DONUT_DEFINES_RENDER


#include <GL/glew.h>
#ifndef GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GL3
#endif
#include <GLFW/glfw3.h>

#include <math.h>
#include <string>

namespace Donut 
{

 	struct TContextDetail
 	{
 		std::string windowName;
 		int width;
 		int lenght;
 		int major;
 		int minor;
 		bool fullScreen;
 	};

	struct TColorFilter
	{
		TColorFilter(float parR, float parG, float parB, float parA) :
		r(parR), 
		g(parG), 
		b(parB), 
		a(parA)
		{
		}

		TColorFilter& operator = (const TColorFilter& parFilter)
		{
			r = parFilter.r;
			g = parFilter.g;
			b = parFilter.b;
			a = parFilter.a;
			return *this;
		}
		float r;
		float g;
		float b;
		float a;
	};

#define DEFAULTW 1280 
#define DEFAULTL 720

#define DEFAULTNAME "Donut"
#define DEFAULTFULLSCREEN false


#define BASIC_VERTEX_SHADER "shaders/base/vertex.glsl"
#define BASIC_FRAGMENT_SHADER "shaders/base/fragment.glsl" 

}
#endif //DONUT_DEFINES_RENDER
