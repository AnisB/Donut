


#ifndef DONUT_MATH_FLOATN
#define DONUT_MATH_FLOATN

struct float1
{
	float1()
	{
		x = 0;
	}

	float1(float parX)
	{
		x = parX;
	}
	float1(const float1& parFloat1)
	{
		this->x = parFloat1.x;
	}

	float x;
};


struct float2
{
	float2()
	{
		x = 0;
		y = 0;
	}

	float2(float parX, float parY)
	{
		x = parX;
		y = parY;
	}
	float2(const float2& parFloat2)
	{
		this->x = parFloat2.x;
		this->y = parFloat2.y;
	}

	const float2 operator- (const float2& parFloat2) const
	{
		float2 result;
		result.x = (this->x - parFloat2.x);
		result.y = (this->y - parFloat2.y);
		return result;
	}

	float2& operator+=(const float2& parFloat2)
	{
		this->x += parFloat2.x;
		this->y += parFloat2.y;
		return *this;
	}

	float x;
	float y;
};

struct float3
{
	float3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	float3(float parX, float parY, float parZ)
	{
		x = parX;
		y = parY;
		z = parZ;
	}
	float3(const float3& parFloat3)
	{
		this->x = parFloat3.x;
		this->y = parFloat3.y;
		this->z = parFloat3.z;
	}

	float x;
	float y;
	float z;
};
#endif