#include "Matrix4.h"

#include <math.h>

Matrix4::Matrix4(MatrixInit::Type reset)
{
	m = new double*[4];
	for(int i = 0; i<4; ++i)
	{
		m[i] = new double[4];
	}
	if (reset == MatrixInit::Zero)
		resetToZero();
	else if (reset == MatrixInit::Identity)
		setIdentity();
}

Matrix4::Matrix4(const Matrix4& parMatrix)
{
	m = new double*[4];
	for(int i = 0; i<4; ++i)
	{
		m[i] = new double[4];
	}
	memcpy(m,parMatrix.m,16);
}
Matrix4::~Matrix4()
{
	delete [] m;
}


void Matrix4::setIdentity()
{
	
	m[0][0] = 1.0;
	m[0][1] = 0.0;
	m[0][2] = 0.0;
	m[0][3] = 0.0;
	
	m[1][0] = 0.0;
	m[1][1] = 1.0;
	m[1][2] = 0.0;
	m[1][3] = 0.0;
	
	m[2][0] = 0.0;
	m[2][1] = 0.0;
	m[2][2] = 1.0;
	m[2][3] = 0.0;
	
	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = 1.0;
}

double Matrix4::det() const
{
	//TODO
	return 0.0;
}
void Matrix4::resetToZero()
{
	m[0][0] = 0.0;
	m[0][1] = 0.0;
	m[0][2] = 0.0;
	m[0][3] = 0.0;

	m[1][0] = 0.0;
	m[1][1] = 0.0;
	m[1][2] = 0.0;
	m[1][3] = 0.0;
	
	m[2][0] = 0.0;
	m[2][1] = 0.0;
	m[2][2] = 0.0;
	m[2][3] = 0.0;

	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = 0.0;
}

Vector3 Matrix4::getTranslate()
{
	// IL Y AUN PROBLEME ICI TODO
	return Vector3(m[0][3],m[1][3],m[2][3]);
}

Vector3 Matrix4::xAxis()
{
	return Vector3(m[0][0],m[1][0],m[2][0]);
}
Vector3 Matrix4::yAxis()
{
	return Vector3(m[0][1],m[1][1],m[2][1]);
}
Vector3 Matrix4::zAxis()
{
	return Vector3(m[0][2],m[1][2],m[2][2]);
}
Vector4 operator*(const Vector4& parFactor)
{
	Vector4 result;
	return result;
}
Matrix4 Matrix4::translate(const Vector4& parVector)
{
	Matrix4 result(MatrixInit::None);
	result.m[0][0] = 0.0;
	result.m[0][1] = 0.0;
	result.m[0][2] = 0.0;
	result.m[0][3] = 0.0;

	result.m[1][0] = 0.0;
	result.m[1][1] = 0.0;
	result.m[1][2] = 0.0;
	result.m[1][3] = 0.0;
	
	result.m[2][0] = 0.0;
	result.m[2][1] = 0.0;
	result.m[2][2] = 0.0;
	result.m[2][3] = 0.0;

	result.m[3][0] = parVector.x;
	result.m[3][1] = parVector.y;
	result.m[3][2] = parVector.z;
	result.m[3][3] = parVector.w;
	return result;
}


Matrix4 Matrix4::translate(const Vector3& parVector)
{
	Matrix4 result(MatrixInit::None);
	result.m[0][0] = 1.0;
	result.m[0][1] = 0.0;
	result.m[0][2] = 0.0;
	result.m[0][3] = parVector.x;

	result.m[1][0] = 0.0;
	result.m[1][1] = 1.0;
	result.m[1][2] = 0.0;
	result.m[1][3] = parVector.y;
	
	result.m[2][0] = 0.0;
	result.m[2][1] = 0.0;
	result.m[2][2] = 1.0;
	result.m[2][3] = parVector.z;

	result.m[3][0] = 0.0;
	result.m[3][1] = 0.0;
	result.m[3][2] = 0.0;
	result.m[3][3] = 1.0;
	return result;
}

Matrix4 Matrix4::rotateXAxis(double parAngle)
{
	double cosVal = cos(parAngle);
	double sinVal = sin(parAngle);
	Matrix4 result(MatrixInit::None);
	result.m[0][0] = 1.0;
	result.m[0][1] = 0.0;
	result.m[0][2] = 0.0;
	result.m[0][3] = 0.0;

	result.m[1][0] = 0.0;
	result.m[1][1] = cosVal;
	result.m[1][2] = -sinVal;
	result.m[1][3] = 0.0;
	
	result.m[2][0] = 0.0;
	result.m[2][1] = sinVal;
	result.m[2][2] = cosVal;
	result.m[2][3] = 0.0;

	result.m[3][0] = 0.0;
	result.m[3][1] = 0.0;
	result.m[3][2] = 0.0;
	result.m[3][3] = 1.0;
	return result;
}

Matrix4 Matrix4::rotateYAxis(double parAngle)
{
	double cosVal = cos(parAngle);
	double sinVal = sin(parAngle);
	Matrix4 result(MatrixInit::None);
	result.m[0][0] = cosVal;
	result.m[0][1] = 0.0;
	result.m[0][2] = sinVal;
	result.m[0][3] = 0.0;

	result.m[1][0] = 0.0;
	result.m[1][1] = 1.0;
	result.m[1][2] = 0.0;
	result.m[1][3] = 0.0;
	
	result.m[2][0] = -sinVal;
	result.m[2][1] = 0.0;
	result.m[2][2] = cosVal;
	result.m[2][3] = 0.0;

	result.m[3][0] = 0.0;
	result.m[3][1] = 0.0;
	result.m[3][2] = 0.0;
	result.m[3][3] = 1.0;
	return result;
}

Matrix4 Matrix4::rotateZAxis(double parAngle)
{
	double cosVal = cos(parAngle);
	double sinVal = sin(parAngle);
	Matrix4 result(MatrixInit::None);
	result.m[0][0] = cosVal;
	result.m[0][1] = -sinVal;
	result.m[0][2] = 0.0;
	result.m[0][3] = 0.0;

	result.m[1][0] = sinVal;
	result.m[1][1] = cosVal;
	result.m[1][2] = 0.0;
	result.m[1][3] = 0.0;
	
	result.m[2][0] = 0.0;
	result.m[2][1] = 0.0;
	result.m[2][2] = 1.0;
	result.m[2][3] = 0.0;

	result.m[3][0] = 0.0;
	result.m[3][1] = 0.0;
	result.m[3][2] = 0.0;
	result.m[3][3] = 1.0;
	return result;
}

Matrix4& Matrix4::operator=(const Matrix4& parMatrix)
{
	m[0][0] = parMatrix.m[0][0];
	m[0][1] = parMatrix.m[0][1];
	m[0][2] = parMatrix.m[0][2];
	m[0][3] = parMatrix.m[0][3];

	m[1][0] = parMatrix.m[1][0];
	m[1][1] = parMatrix.m[1][1];
	m[1][2] = parMatrix.m[1][2];
	m[1][3] = parMatrix.m[1][3];
	
	m[2][0] = parMatrix.m[2][0];
	m[2][1] = parMatrix.m[2][1];
	m[2][2] = parMatrix.m[2][2];
	m[2][3] = parMatrix.m[2][3];

	m[3][0] = parMatrix.m[3][0];
	m[3][1] = parMatrix.m[3][1];
	m[3][2] = parMatrix.m[3][2];
	m[3][3] = parMatrix.m[3][3];
	return *this;
}
Matrix4 Matrix4::operator*(const Matrix4& parMatrix )
{
	Matrix4 result(MatrixInit::None);
	result.m[0][0] = m[0][0] * parMatrix.m[0][0] + m[0][1] * parMatrix.m[1][0] + m[0][2] * parMatrix.m[2][0] + m[0][3] * parMatrix.m[3][0]; 
	result.m[0][1] = m[0][0] * parMatrix.m[0][1] + m[0][1] * parMatrix.m[1][1] + m[0][2] * parMatrix.m[2][1] + m[0][3] * parMatrix.m[3][1]; 
	result.m[0][2] = m[0][0] * parMatrix.m[0][2] + m[0][1] * parMatrix.m[1][2] + m[0][2] * parMatrix.m[2][2] + m[0][3] * parMatrix.m[3][2]; 
	result.m[0][3] = m[0][0] * parMatrix.m[0][3] + m[0][1] * parMatrix.m[1][3] + m[0][2] * parMatrix.m[2][3] + m[0][3] * parMatrix.m[3][3]; 
	result.m[1][0] = m[1][0] * parMatrix.m[0][0] + m[1][1] * parMatrix.m[1][0] + m[1][2] * parMatrix.m[2][0] + m[1][3] * parMatrix.m[3][0]; 
	result.m[1][1] = m[1][0] * parMatrix.m[0][1] + m[1][1] * parMatrix.m[1][1] + m[1][2] * parMatrix.m[2][1] + m[1][3] * parMatrix.m[3][1]; 
	result.m[1][2] = m[1][0] * parMatrix.m[0][2] + m[1][1] * parMatrix.m[1][2] + m[1][2] * parMatrix.m[2][2] + m[1][3] * parMatrix.m[3][2]; 
	result.m[1][3] = m[1][0] * parMatrix.m[0][3] + m[1][1] * parMatrix.m[1][3] + m[1][2] * parMatrix.m[2][3] + m[1][3] * parMatrix.m[3][3]; 
	result.m[2][0] = m[2][0] * parMatrix.m[0][0] + m[2][1] * parMatrix.m[1][0] + m[2][2] * parMatrix.m[2][0] + m[2][3] * parMatrix.m[3][0]; 
	result.m[2][1] = m[2][0] * parMatrix.m[0][1] + m[2][1] * parMatrix.m[1][1] + m[2][2] * parMatrix.m[2][1] + m[2][3] * parMatrix.m[3][1]; 
	result.m[2][2] = m[2][0] * parMatrix.m[0][2] + m[2][1] * parMatrix.m[1][2] + m[2][2] * parMatrix.m[2][2] + m[2][3] * parMatrix.m[3][2]; 
	result.m[2][3] = m[2][0] * parMatrix.m[0][3] + m[2][1] * parMatrix.m[1][3] + m[2][2] * parMatrix.m[2][3] + m[2][3] * parMatrix.m[3][3]; 
	result.m[3][0] = m[3][0] * parMatrix.m[0][0] + m[3][1] * parMatrix.m[1][0] + m[3][2] * parMatrix.m[2][0] + m[3][3] * parMatrix.m[3][0]; 
	result.m[3][1] = m[3][0] * parMatrix.m[0][1] + m[3][1] * parMatrix.m[1][1] + m[3][2] * parMatrix.m[2][1] + m[3][3] * parMatrix.m[3][1]; 
	result.m[3][2] = m[3][0] * parMatrix.m[0][2] + m[3][1] * parMatrix.m[1][2] + m[3][2] * parMatrix.m[2][2] + m[3][3] * parMatrix.m[3][2]; 
	result.m[3][3] = m[3][0] * parMatrix.m[0][3] + m[3][1] * parMatrix.m[1][3] + m[3][2] * parMatrix.m[2][3] + m[3][3] * parMatrix.m[3][3]; 
	return result;
}
Matrix4 Matrix4::inverse(const Matrix4& parMatrix)
{
	Matrix4 inverseMatrix;
	// TODO
	return inverseMatrix;
}

void Matrix4::toTable(float* content) const
{
}

std::ostream& operator<< (std::ostream& os, const Matrix4& obj) 
{
	os << "Matrix4\n("<<obj.m[0][0] <<", " <<obj.m[0][1]<<", "<<obj.m[0][2]<<", " << obj.m[0][3]<<",\n"
		<<obj.m[1][0] <<", " <<obj.m[1][1]<<", "<<obj.m[1][2]<<", " << obj.m[1][3]<<",\n"
		<<obj.m[2][0] <<", " <<obj.m[2][1]<<", "<<obj.m[2][2]<<", " << obj.m[2][3]<<",\n"
		<<obj.m[3][0] <<", " <<obj.m[3][1]<<", "<<obj.m[3][2]<<", " << obj.m[3][3]<<")";
	return os;
}     
