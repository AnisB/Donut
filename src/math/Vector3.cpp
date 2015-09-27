#include "Vector3.h"

#include <math.h>

Vector3::Vector3()
: x(0.0)
, y(0.0)
, z(0.0)
{
}

Vector3::Vector3(double parX, double parY, double parZ)
: x(parX)
, y(parY)
, z(parZ)
{
}

Vector3::Vector3(const Vector3& parVec)
    : x(parVec.x)
    , y(parVec.y)
    , z(parVec.z)
{
}

Vector3::~Vector3()
{
}

double Vector3::Norm()
{
	return sqrt( x*x + y*y +z*z);
}

Vector3& Vector3::operator*=(double parFactor)
{
	x*= parFactor;
	y*= parFactor;
	z*= parFactor;
	return *this;
}

Vector3 Vector3::operator*(double parFactor) const
{
	Vector3 result;
	result.x= parFactor*x;
	result.y= parFactor*y;
	result.z= parFactor*z;
	return result;
}
		
Vector3 Vector3::operator+(const Vector3& parVect) const
{
	Vector3 result;
	result.x= parVect.x+x;
	result.y= parVect.y+y;
	result.z= parVect.z+z;
	return result;
}
Vector3 Vector3::operator-(const Vector3& parVect) const
{
	Vector3 result;
	result.x= x-parVect.x;
	result.y= y-parVect.y;
	result.z= z-parVect.z;
	return result;
}
Vector3 Vector3::operator*(const Matrix3& parMatrix)
{
	Vector3 result;
	result.x = x* parMatrix.m[0][0] + y* parMatrix.m[1][0] + z* parMatrix.m[2][0];
	result.y = x* parMatrix.m[0][1] + y* parMatrix.m[1][1] + z* parMatrix.m[2][1];
	result.z = x* parMatrix.m[0][2] + y* parMatrix.m[1][2] + z* parMatrix.m[2][2];
	return result;	
}
double Vector3::dotProduct(const Vector3& parV1, const Vector3& parV2)
{
	return ( parV1.x*parV2.x + parV1.y*parV2.y +parV1.z*parV2.z);
}


Vector3 Vector3::crossProduct(const Vector3& parV1, const Vector3& parV2)
{
	Vector3 result;
	result.x = parV1.y * parV2.z - parV2.y * parV1.z;
	result.y = parV1.z * parV2.x - parV2.z * parV1.x;
	result.z = parV1.x * parV2.y - parV2.x * parV1.y; 
	return result;
}

std::ostream& operator<< (std::ostream& os, const Vector3& obj) 
{
       os << "Vec3("<<obj.x <<", " <<obj.y<<", "<<obj.z << ")";
       return os;
}     

Vector3 Vector3::operator/(double parFactor) const
{
	Vector3 result;
	result.x= x/parFactor;
	result.y= y/parFactor;
	result.z= z/parFactor;
	return result;
}
