#include "Matrix3.h"


Matrix3::Matrix3()
{
	m = new double*[3];
	for(int i = 0; i<3; ++i)
	{
		m[i] = new double[3];
	}
	resetToZero();
}

Matrix3::Matrix3(const Matrix3& parMatrix)
{
	m = new double*[3];
	for(int i = 0; i<3; ++i)
	{
		m[i] = new double[3];
	}
	memcpy(m,parMatrix.m,9);
}

Matrix3::~Matrix3()
{
	delete [] m;
}


void Matrix3::setIdentity()
{
	m[0][0] = 1.0;
	m[0][1] = 0.0;
	m[0][2] = 0.0;
	
	m[1][0] = 0.0;
	m[1][1] = 1.0;
	m[1][2] = 0.0;
	
	m[2][0] = 0.0;
	m[2][1] = 0.0;
	m[2][2] = 1.0;
}

double Matrix3::det() const
{
	return (m[0][0]*m[1][1]*m[2][2]-m[2][1]*m[1][2])
           -m[0][1]*(m[1][0]*m[2][2]-m[1][2]*m[2][0])
           +m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
}
void Matrix3::resetToZero()
{
	m[0][0] = 0.0;
	m[0][1] = 0.0;
	m[0][2] = 0.0;
	
	m[1][0] = 0.0;
	m[1][1] = 0.0;
	m[1][2] = 0.0;
	
	m[2][0] = 0.0;
	m[2][1] = 0.0;
	m[2][2] = 0.0;
}


Vector3 Matrix3::operator*=(const Vector3& parFactor)
{
	Vector3 result;
	result.x = parFactor.x* m[0][0] + parFactor.y* m[0][1] +parFactor.z* m[0][2];
	result.y = parFactor.x* m[1][0] + parFactor.y* m[1][1] +parFactor.z* m[1][2];
	result.z = parFactor.x* m[2][0] + parFactor.y* m[2][1] +parFactor.z* m[2][2];
	return result;
}

Matrix3& Matrix3::operator=(const Matrix3& parMatrix)
{
	memcpy(m,parMatrix.m,9);
	return *this;
}
Matrix3 Matrix3::inverse(const Matrix3& parMatrix)
{
	Matrix3 inverseMatrix;
	double invdet = 1.0/parMatrix.det();
	inverseMatrix.m[0][0] =  (parMatrix.m[1][1]*parMatrix.m[2][2]-parMatrix.m[2][1]*parMatrix.m[1][2])*invdet;
	inverseMatrix.m[1][0] = -(parMatrix.m[0][1]*parMatrix.m[2][2]-parMatrix.m[0][2]*parMatrix.m[2][1])*invdet;
	inverseMatrix.m[2][0] =  (parMatrix.m[0][1]*parMatrix.m[1][2]-parMatrix.m[0][2]*parMatrix.m[1][1])*invdet;
	inverseMatrix.m[0][1] = -(parMatrix.m[1][0]*parMatrix.m[2][2]-parMatrix.m[1][2]*parMatrix.m[2][0])*invdet;
	inverseMatrix.m[1][1] =  (parMatrix.m[0][0]*parMatrix.m[2][2]-parMatrix.m[0][2]*parMatrix.m[2][0])*invdet;
	inverseMatrix.m[2][1] = -(parMatrix.m[0][0]*parMatrix.m[1][2]-parMatrix.m[1][0]*parMatrix.m[0][2])*invdet;
	inverseMatrix.m[0][2] =  (parMatrix.m[1][0]*parMatrix.m[2][1]-parMatrix.m[2][0]*parMatrix.m[1][1])*invdet;
	inverseMatrix.m[1][2] = -(parMatrix.m[0][0]*parMatrix.m[2][1]-parMatrix.m[2][0]*parMatrix.m[0][1])*invdet;
	inverseMatrix.m[2][2] =  (parMatrix.m[0][0]*parMatrix.m[1][1]-parMatrix.m[1][0]*parMatrix.m[0][1])*invdet;
	return inverseMatrix;
}

std::ostream& operator<< (std::ostream& os, const Matrix3& obj) 
{
	os << "Matrix3\n("<<obj.m[0][0] <<", " <<obj.m[0][1]<<", "<<obj.m[0][2]<<",\n"
		<<obj.m[1][0] <<", " <<obj.m[1][1]<<", "<<obj.m[1][2]<<",\n"
		<<obj.m[2][0] <<", " <<obj.m[2][1]<<", "<<obj.m[2][2]<<")";
	return os;
}     
