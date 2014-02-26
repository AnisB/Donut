


#ifndef DONUT_MATH_TVEC
#define DONUT_MATH_TVEC

#include "Base/DebugPrinters.h"


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

static TVec2 operator-(const TVec2& parVec1, const TVec2& parVec2)
{
	TVec2 result;
	result.val[0] = (parVec1.val[0]-parVec2.val[0]);
	result.val[1] = (parVec1.val[1]-parVec2.val[1]);
	return result;
}
static TVec2 operator+(const TVec2& parVec1, const TVec2& parVec2)
{
	TVec2 result;
	result.val[0] = (parVec1.val[0]+parVec2.val[0]);
	result.val[1] = (parVec1.val[1]+parVec2.val[1]);
	return result;
}

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