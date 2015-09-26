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


#ifndef DONUT_MATH_TVEC
#define DONUT_MATH_TVEC

struct TVec1
{
	TVec1()
	{
	}

	TVec1(float parX)
	{
		val[0] = parX;
	}
	TVec1(const TVec1& parTVec1)
	{
		val[0] = parTVec1.val[0];
	}

	float val[1];
};


struct TVec2
{
	TVec2()
	{
	}

	TVec2(float parX, float parY)
	{
		val[0] = parX;
		val[1] = parY;
	}
	TVec2(const TVec2& parTVec2)
	{
		val[0] = parTVec2.val[0];
		val[1] = parTVec2.val[1];
	}
	void operator+=(const TVec2& parTVec2)
	{
		val[0] += parTVec2.val[0];
		val[1] += parTVec2.val[1];
	}

	float val[2];
};

TVec2 operator*(float parScale, const TVec2& parTVec1);
TVec2 operator-(const TVec2& parVec1, const TVec2& parVec2);
TVec2 operator+(const TVec2& parVec1, const TVec2& parVec2);
struct TVec3
{
	TVec3(float parDefault = 0.0)
	{
		val[0] = parDefault;
		val[1] = parDefault;
		val[2] = parDefault;
	}

	TVec3(float parX, float parY, float parZ)
	{
		val[0] = parX;
		val[1] = parY;
		val[2] = parZ;
	}
	TVec3(const TVec3& parTVec3)
	{
		val[0] = parTVec3.val[0];
		val[1] = parTVec3.val[1];
		val[2] = parTVec3.val[2];
	}
	void operator+=(const TVec3& parTVec3)
	{
		val[0] += parTVec3.val[0];
		val[1] += parTVec3.val[1];
		val[2] += parTVec3.val[2];
	}

	float val[3];
};

TVec3 operator+(const TVec3& parTVec1, const TVec3& parTVec2);
TVec3 operator-(const TVec3& parTVec1, const TVec3& parTVec2);
TVec3 operator-(const TVec3& parTVec2);
TVec3 operator*(const TVec3& parTVec1, const TVec3& parTVec2);
TVec3 operator*(const TVec3& parTVec1, float parScale);
float dot(const TVec3& parTVec1, const TVec3& parTVec2);
TVec3 operator^(const TVec3& parTVec1, const TVec3& parTVec2);

struct TVec4
{
	TVec4(float parDefault = 0.0)
	{
		val[0] = parDefault;
		val[1] = parDefault;
		val[2] = parDefault;
		val[3] = parDefault;
	}

	TVec4(float parX, float parY, float parZ, float parW)
	{
		val[0] = parX;
		val[1] = parY;
		val[2] = parZ;
		val[3] = parW;
	}
	TVec4(const TVec4& parTVec4)
	{
		val[0] = parTVec4.val[0];
		val[1] = parTVec4.val[1];
		val[2] = parTVec4.val[2];
		val[3] = parTVec4.val[3];
	}

	float val[4];
};
#endif