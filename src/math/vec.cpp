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

#include <math/vec.h>

// VEC2 METHODS
TVec2 operator*(float parScale, const TVec2& parTVec1)
{
	return TVec2(parTVec1.val[0]*parScale, parTVec1.val[1]*parScale);	
}
TVec2 operator-(const TVec2& parVec1, const TVec2& parVec2)
{
	return TVec2(parVec1.val[0]-parVec2.val[0],parVec1.val[1]-parVec2.val[1]);
}

TVec2 operator+(const TVec2& parVec1, const TVec2& parVec2)
{
	TVec2 result;
	result.val[0] = (parVec1.val[0]+parVec2.val[0]);
	result.val[1] = (parVec1.val[1]+parVec2.val[1]);
	return result;
}

// VEC3 METHODS
TVec3 operator*(const TVec3& parTVec1, const TVec3& parTVec2)
{
	return TVec3(parTVec1.val[0]*parTVec2.val[0], parTVec1.val[1]*parTVec2.val[1], parTVec1.val[2]*parTVec2.val[2]);
}
TVec3 operator*(const TVec3& parTVec1, float parScale)
{
	return TVec3(parTVec1.val[0]*parScale, parTVec1.val[1]*parScale, parTVec1.val[2]*parScale);	
}
TVec3 operator+(const TVec3& parTVec1, const TVec3& parTVec2)
{
	return TVec3(parTVec1.val[0]+parTVec2.val[0], parTVec1.val[1]+parTVec2.val[1], parTVec1.val[2]+parTVec2.val[2]);
}
TVec3 operator-(const TVec3& parTVec1)
{
	return TVec3(-parTVec1.val[0], -parTVec1.val[1], -parTVec1.val[2]);
}

TVec3 operator-(const TVec3& parTVec1, const TVec3& parTVec2)
{
	return TVec3(parTVec1.val[0]-parTVec2.val[0], parTVec1.val[1]-parTVec2.val[1], parTVec1.val[2]-parTVec2.val[2]);
}

float dot(const TVec3& parTVec1, const TVec3& parTVec2)
{
	return (parTVec1.val[0]*parTVec2.val[0]+ parTVec1.val[1]*parTVec2.val[1] + parTVec1.val[2]*parTVec2.val[2]);
}

TVec3 operator^(const TVec3& parTVec1, const TVec3& parTVec2)
{
	return TVec3(parTVec1.val[1]*parTVec2.val[2] - parTVec1.val[2]*parTVec2.val[1], 
			parTVec1.val[2]*parTVec2.val[0] - parTVec1.val[0]*parTVec2.val[2], 
			parTVec1.val[0]*parTVec2.val[1] - parTVec1.val[1]*parTVec2.val[0]);
}