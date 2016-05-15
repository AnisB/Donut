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

// Donut includes
#include "matrix3.h"

// STL includes
#include <string.h>

namespace Donut
{
	void matrix3(Matrix3& _mat, MatrixInit::Type reset)
	{
		if (reset == MatrixInit::Zero)
			ResetToZero(_mat);
		else if (reset == MatrixInit::Identity)
			SetIdentity(_mat);
	}

	Matrix3::Matrix3(const Matrix3& _mat)
	{
		memcpy(m, _mat.m, 9*sizeof(double));
	}

	Matrix3& Matrix3::operator=(const Matrix3 _mat)
	{
		memcpy(m, _mat.m, 9*sizeof(double));
		return *this;
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

	void ToTable(const Matrix3& _mat, float* content)
	{
		for(int i = 0; i < 9; ++i)
		{
			content[i] = (float)_mat.m[i];
		}
	}

	Vector3 operator*(const Matrix3& _mat, const Vector3& _vec)
	{
		Vector3 result;
		result.x = _mat.m[0]*_vec.x + _mat.m[1]*_vec.y + _mat.m[2]*_vec.z;
		result.y = _mat.m[3]*_vec.x + _mat.m[4]*_vec.y + _mat.m[5]*_vec.z;
		result.z = _mat.m[6]*_vec.x + _mat.m[7]*_vec.y + _mat.m[8]*_vec.z;
		return result;
	}

	std::ostream& operator<< (std::ostream& os, const Matrix3& obj) 
	{
		os << "Matrix3\n("<<obj.m[0] <<", " <<obj.m[1]<<", "<<obj.m[2]<<",\n"
			<<obj.m[3] <<", " <<obj.m[4]<<", "<<obj.m[5]<<",\n"
			<<obj.m[6] <<", " <<obj.m[7]<<", "<<obj.m[8]<<")";
		return os;
	}     
}