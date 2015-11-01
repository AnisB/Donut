// Library includes
#include "matrix3.h"
// STL includes
#include <string.h>

namespace Donut
{
	Matrix3::Matrix3(const Matrix3& _mat)
	{
		memcpy(m, _mat.m, 9);
	}

	void SetIdentity(Matrix3& _mat)
	{
		_mat.m[0] = 1.0;
		_mat.m[1] = 0.0;
		_mat.m[2] = 0.0;
		
		_mat.m[3] = 0.0;
		_mat.m[4] = 1.0;
		_mat.m[5] = 0.0;
		
		_mat.m[6] = 0.0;
		_mat.m[7] = 0.0;
		_mat.m[8] = 1.0;
	}

	double Det(const Matrix3& _mat)
	{
		return (_mat.m[0]*_mat.m[4]*_mat.m[8]-_mat.m[7]*_mat.m[5])
	           -_mat.m[1]*(_mat.m[3]*_mat.m[8]-_mat.m[5]*_mat.m[6])
	           +_mat.m[2]*(_mat.m[3]*_mat.m[7]-_mat.m[4]*_mat.m[6]);
	}
	void ResetToZero(Matrix3& _mat)
	{
		std::fill_n(_mat.m, 9, 0);
	}

	Matrix3& Set(Matrix3& _mat1, Matrix3& _mat2)
	{
		memcpy(_mat1.m, _mat2.m,9);
		return _mat1;
	}
	Matrix3 Inverse(const Matrix3& _mat)
	{
		Matrix3 inverseMatrix;
		double invdet = 1.0/Det(_mat);
		inverseMatrix.m[0] =  (_mat.m[4]*_mat.m[8]-_mat.m[7]*_mat.m[5])*invdet;
		inverseMatrix.m[3] = -(_mat.m[1]*_mat.m[8]-_mat.m[2]*_mat.m[7])*invdet;
		inverseMatrix.m[6] =  (_mat.m[1]*_mat.m[5]-_mat.m[2]*_mat.m[4])*invdet;
		inverseMatrix.m[1] = -(_mat.m[3]*_mat.m[8]-_mat.m[5]*_mat.m[6])*invdet;
		inverseMatrix.m[4] =  (_mat.m[0]*_mat.m[8]-_mat.m[2]*_mat.m[6])*invdet;
		inverseMatrix.m[7] = -(_mat.m[0]*_mat.m[5]-_mat.m[3]*_mat.m[2])*invdet;
		inverseMatrix.m[2] =  (_mat.m[3]*_mat.m[7]-_mat.m[6]*_mat.m[4])*invdet;
		inverseMatrix.m[5] = -(_mat.m[0]*_mat.m[7]-_mat.m[6]*_mat.m[1])*invdet;
		inverseMatrix.m[8] =  (_mat.m[0]*_mat.m[4]-_mat.m[3]*_mat.m[1])*invdet;
		return inverseMatrix;
	}

	std::ostream& operator<< (std::ostream& os, const Matrix3& obj) 
	{
		os << "Matrix3\n("<<obj.m[0] <<", " <<obj.m[1]<<", "<<obj.m[2]<<",\n"
			<<obj.m[3] <<", " <<obj.m[4]<<", "<<obj.m[5]<<",\n"
			<<obj.m[6] <<", " <<obj.m[7]<<", "<<obj.m[8]<<")";
		return os;
	}     
}