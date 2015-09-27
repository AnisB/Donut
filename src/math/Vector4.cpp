#include "vector4.h"

#include <math.h>


Vector4::Vector4()
: x(0.0)
, y(0.0)
, z(0.0)
, w(0.0)
{
}

Vector4::Vector4(double parX, double parY, double parZ, double parW)
: x(parX)
, y(parY)
, z(parZ)
, w(parW)
{
}

Vector4::Vector4(const Vector4& parVec)
: x(parVec.x)
, y(parVec.y)
, z(parVec.z)
, w(parVec.w)
{
}

Vector4::~Vector4()
{
}

double Vector4::Norm()
{
	return sqrt( x*x + y*y +z*z);
}


Vector4& Vector4::operator*=(double parFactor)
{
	x*= parFactor;
	y*= parFactor;
	z*= parFactor;
	return *this;
}


double Vector4::dotProduct(const Vector4& parV1, const Vector4& parV2)
{
	return ( parV1.x*parV2.x + parV1.y*parV2.y +parV1.z*parV2.z);
}

Vector4 Vector4::crossProduct(const Vector4& parV1, const Vector4& parV2)
{
	Vector4 result;
	result.x = parV1.y * parV2.z - parV2.y * parV1.z;
	result.y = parV1.z * parV2.x - parV2.z * parV1.x;
	result.z = parV1.x * parV2.y - parV2.x * parV1.y; 
	return result;
}



std::ostream& operator<< (std::ostream& os, const Vector4& obj) 
{
       os << "Vec3("<<obj.x <<", " <<obj.y<<", "<<obj.z << ", "<<obj.w<<")";
       return os;
}     
