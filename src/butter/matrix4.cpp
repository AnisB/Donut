#include "Matrix4.h"
#include "base/security.h"
// STL includes
#include <string.h>
#include <math.h>

namespace Donut
{
	void matrix4(Matrix4& _mat, MatrixInit::Type reset)
	{
		if (reset == MatrixInit::Zero)
			ResetToZero(_mat);
		else if (reset == MatrixInit::Identity)
			SetIdentity(_mat);
	}

	Matrix4::Matrix4(const Matrix4& _mat)
	{
		memcpy(m, _mat.m,16*sizeof(double));
	}

	void AsPerspective(Matrix4& _mat, double parFovy, double parAspect, double parNear, double parFar)
	{
		std::fill_n(_mat.m, 16, 0);
		double f = 1/tan(parFovy*3.14/360.0);
		_mat.m[0] = f/parAspect;
		_mat.m[5] = f;
		_mat.m[10] = (parFar+parNear)/(parNear-parFar);
		_mat.m[11] = (2*parFar*parNear)/(parNear-parFar);
		_mat.m[14] = -1;
	}

	void SetIdentity(Matrix4& _mat)
	{	
		std::fill_n(_mat.m, 16, 0);
		_mat.m[0] = 1.0;
		_mat.m[5] = 1.0;
		_mat.m[10] = 1.0;
		_mat.m[15] = 1.0;
	}

	double Det(const Matrix4& _mat)
	{
		//TODO
		ASSERT_NOT_IMPLEMENTED();
		return 0.0;
	}

	void ResetToZero(Matrix4& _mat)
	{
		// MEM set
		std::fill_n(_mat.m, 16, 0);
	}

	Vector3 GetTranslate(const Matrix4& _mat)
	{
		// IL Y AUN PROBLEME ICI TODO
		return vector3(_mat.m[3],_mat.m[7],_mat.m[11]);
	}

	Vector3 XAxis(const Matrix4& _mat)
	{
		return vector3(_mat.m[0],_mat.m[4],_mat.m[8]);
	}
	Vector3 YAxis(const Matrix4& _mat)
	{
		return vector3(_mat.m[1], _mat.m[5], _mat.m[9]);
	}

	Vector3 ZAxis(const Matrix4& _mat)
	{
		return vector3(_mat.m[2], _mat.m[6], _mat.m[10]);
	}

	Vector4 operator*(const Matrix4& _mat, const Vector4& parFactor)
	{
		ASSERT_NOT_IMPLEMENTED();
		return Vector4();
	}

	Matrix4 Translate_M4(const Vector4& parVector)
	{
		Matrix4 result;
		result.m[0] = 1.0;
		result.m[1] = 0.0;
		result.m[2] = 0.0;
		result.m[3] = parVector.x;

		result.m[4] = 0.0;
		result.m[5] = 1.0;
		result.m[6] = 0.0;
		result.m[7] = parVector.y;
		
		result.m[8] = 0.0;
		result.m[9] = 0.0;
		result.m[10] = 1.0;
		result.m[11] = parVector.z;

		result.m[12] = 0.0;
		result.m[13] = 0.0;
		result.m[14] = 0.0;
		result.m[15] = parVector.w;
		return result;
	}


	Matrix4 Translate_M4(const Vector3& parVector)
	{
		Matrix4 result;
		result.m[0] = 1.0;
		result.m[1] = 0.0;
		result.m[2] = 0.0;
		result.m[3] = parVector.x;

		result.m[4] = 0.0;
		result.m[5] = 1.0;
		result.m[6] = 0.0;
		result.m[7] = parVector.y;
		
		result.m[8] = 0.0;
		result.m[9] = 0.0;
		result.m[10] = 1.0;
		result.m[11] = parVector.z;

		result.m[12] = 0.0;
		result.m[13] = 0.0;
		result.m[14] = 0.0;
		result.m[15] = 1.0;
		return result;
	}

	Matrix4 RotateXAxis(double parAngle)
	{
		double cosVal = cos(parAngle);
		double sinVal = sin(parAngle);
		Matrix4 result;
		result.m[0] = 1.0;
		result.m[1] = 0.0;
		result.m[2] = 0.0;
		result.m[3] = 0.0;

		result.m[4] = 0.0;
		result.m[5] = cosVal;
		result.m[6] = -sinVal;
		result.m[7] = 0.0;
		
		result.m[8] = 0.0;
		result.m[9] = sinVal;
		result.m[10] = cosVal;
		result.m[11] = 0.0;

		result.m[12] = 0.0;
		result.m[13] = 0.0;
		result.m[14] = 0.0;
		result.m[15] = 1.0;
		return result;
	}

	Matrix4 RotateYAxis(double parAngle)
	{
		double cosVal = cos(parAngle);
		double sinVal = sin(parAngle);
		Matrix4 result;
		result.m[0] = cosVal;
		result.m[1] = 0.0;
		result.m[2] = sinVal;
		result.m[3] = 0.0;

		result.m[4] = 0.0;
		result.m[5] = 1.0;
		result.m[6] = 0.0;
		result.m[7] = 0.0;
		
		result.m[8] = -sinVal;
		result.m[9] = 0.0;
		result.m[10] = cosVal;
		result.m[11] = 0.0;

		result.m[12] = 0.0;
		result.m[13] = 0.0;
		result.m[14] = 0.0;
		result.m[15] = 1.0;
		return result;
	}

	Matrix4 RotateZAxis(double parAngle)
	{
		double cosVal = cos(parAngle);
		double sinVal = sin(parAngle);
		Matrix4 result;
		result.m[0] = cosVal;
		result.m[1] = -sinVal;
		result.m[2] = 0.0;
		result.m[3] = 0.0;

		result.m[4] = sinVal;
		result.m[5] = cosVal;
		result.m[6] = 0.0;
		result.m[7] = 0.0;
		
		result.m[8] = 0.0;
		result.m[9] = 0.0;
		result.m[10] = 1.0;
		result.m[11] = 0.0;

		result.m[12] = 0.0;
		result.m[13] = 0.0;
		result.m[14] = 0.0;
		result.m[15] = 1.0;
		return result;
	}

	Matrix4& Set(Matrix4& _target, const Matrix4& _source)
	{
		_target.m[0] = _source.m[0];
		_target.m[1] = _source.m[1];
		_target.m[2] = _source.m[2];
		_target.m[3] = _source.m[3];

		_target.m[4] = _source.m[4];
		_target.m[5] = _source.m[5];
		_target.m[6] = _source.m[6];
		_target.m[7] = _source.m[7];
		
		_target.m[8] = _source.m[8];
		_target.m[9] = _source.m[9];
		_target.m[10] = _source.m[10];
		_target.m[11] = _source.m[11];

		_target.m[12] = _source.m[12];
		_target.m[13] = _source.m[13];
		_target.m[14] = _source.m[14];
		_target.m[15] = _source.m[15];
		return _target;
	}

	Matrix4 operator*(const Matrix4& _mat1, const Matrix4& _mat2 )
	{
		Matrix4 result;
		result.m[0] = _mat1.m[0] * _mat2.m[0] + _mat1.m[1] * _mat2.m[4] + _mat1.m[2] * _mat2.m[8] + _mat1.m[3] * _mat2.m[12]; 
		result.m[1] = _mat1.m[0] * _mat2.m[1] + _mat1.m[1] * _mat2.m[5] + _mat1.m[2] * _mat2.m[9] + _mat1.m[3] * _mat2.m[13]; 
		result.m[2] = _mat1.m[0] * _mat2.m[2] + _mat1.m[1] * _mat2.m[6] + _mat1.m[2] * _mat2.m[10] + _mat1.m[3] * _mat2.m[14]; 
		result.m[3] = _mat1.m[0] * _mat2.m[3] + _mat1.m[1] * _mat2.m[7] + _mat1.m[2] * _mat2.m[11] + _mat1.m[3] * _mat2.m[15]; 
		result.m[4] = _mat1.m[4] * _mat2.m[0] + _mat1.m[5] * _mat2.m[4] + _mat1.m[6] * _mat2.m[8] + _mat1.m[7] * _mat2.m[12]; 
		result.m[5] = _mat1.m[4] * _mat2.m[1] + _mat1.m[5] * _mat2.m[5] + _mat1.m[6] * _mat2.m[9] + _mat1.m[7] * _mat2.m[13]; 
		result.m[6] = _mat1.m[4] * _mat2.m[2] + _mat1.m[5] * _mat2.m[6] + _mat1.m[6] * _mat2.m[10] + _mat1.m[7] * _mat2.m[14]; 
		result.m[7] = _mat1.m[4] * _mat2.m[3] + _mat1.m[5] * _mat2.m[7] + _mat1.m[6] * _mat2.m[11] + _mat1.m[7] * _mat2.m[15]; 
		result.m[8] = _mat1.m[8] * _mat2.m[0] + _mat1.m[9] * _mat2.m[4] + _mat1.m[10] * _mat2.m[8] + _mat1.m[11] * _mat2.m[12]; 
		result.m[9] = _mat1.m[8] * _mat2.m[1] + _mat1.m[9] * _mat2.m[5] + _mat1.m[10] * _mat2.m[9] + _mat1.m[11] * _mat2.m[13]; 
		result.m[10] = _mat1.m[8] * _mat2.m[2] + _mat1.m[9] * _mat2.m[6] + _mat1.m[10] * _mat2.m[10] + _mat1.m[11] * _mat2.m[14]; 
		result.m[11] = _mat1.m[8] * _mat2.m[3] + _mat1.m[9] * _mat2.m[7] + _mat1.m[10] * _mat2.m[11] + _mat1.m[11] * _mat2.m[15]; 
		result.m[12] = _mat1.m[12] * _mat2.m[0] + _mat1.m[13] * _mat2.m[4] + _mat1.m[14] * _mat2.m[8] + _mat1.m[15] * _mat2.m[12]; 
		result.m[13] = _mat1.m[12] * _mat2.m[1] + _mat1.m[13] * _mat2.m[5] + _mat1.m[14] * _mat2.m[9] + _mat1.m[15] * _mat2.m[13]; 
		result.m[14] = _mat1.m[12] * _mat2.m[2] + _mat1.m[13] * _mat2.m[6] + _mat1.m[14] * _mat2.m[10] + _mat1.m[15] * _mat2.m[14]; 
		result.m[15] = _mat1.m[12] * _mat2.m[3] + _mat1.m[13] * _mat2.m[7] + _mat1.m[14] * _mat2.m[11] + _mat1.m[15] * _mat2.m[15]; 
		return result;
	}

	Matrix4 inverse(const Matrix4& parMatrix)
	{
		Matrix4 inverseMatrix;
		ASSERT_NOT_IMPLEMENTED();
		return inverseMatrix;
	}

	void ToTable(const Matrix4& _mat, float* content)
	{
		for(int i = 0; i < 16; ++i)
		{
			content[i] = (float)_mat.m[i];
		}
	}

	std::ostream& operator<< (std::ostream& os, const Matrix4& obj) 
	{
		os << "Matrix4\n("<<obj.m[0] <<", " <<obj.m[1]<<", "<<obj.m[2]<<", " << obj.m[3]<<",\n"
			<<obj.m[4] <<", " <<obj.m[5]<<", "<<obj.m[6]<<", " << obj.m[7]<<",\n"
			<<obj.m[8] <<", " <<obj.m[9]<<", "<<obj.m[10]<<", " << obj.m[11]<<",\n"
			<<obj.m[12] <<", " <<obj.m[13]<<", "<<obj.m[14]<<", " << obj.m[15]<<")";
		return os;
	}     
}