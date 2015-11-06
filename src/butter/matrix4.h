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
#ifndef BUTTER_MATRIX4_H
#define BUTTER_MATRIX4_H

#include "vector3.h"

#include <iostream>

namespace Donut
{
	// Init Functions
	void matrix4(Matrix4& _mat, MatrixInit::Type _init = MatrixInit::Zero);
	void SetIdentity(Matrix4& _matrix);
	void ResetToZero(Matrix4& _matrix);
	void AsPerspective(Matrix4& _mat, double parFovy, double parAspect, double parNear, double parFar);

	// Access functions
	Vector3 GetTranslate(const Matrix4& _matrix);
	Vector3 XAxis(const Matrix4& _matrix);
	Vector3 YAxis(const Matrix4& _matrix);
	Vector3 ZAxis(const Matrix4& _matrix);
	
	// Computing functions
	double Det(const Matrix4& _matrix);
	Matrix4 Inverse(const Matrix4& parMatrix);
	Matrix4 Translate_M4(const Vector4& parVector);
	Matrix4 Translate_M4(const Vector3& parVector);

	Matrix4 Rotate(double parAngle, const Vector3& parAxis);
	void ToTable(const Matrix4& _matrix, float* content);

	Matrix4 RotateXAxis(double parAngle);
	Matrix4 RotateYAxis(double parAngle);
	Matrix4 RotateZAxis(double parAngle);

	Vector4 operator*(const Matrix4& _mat, const Vector4& _fac);
	Matrix4 operator*(const Matrix4& _mat1, const Matrix4& _mat2);
	Matrix4& Set(Matrix4& _target, const Matrix4& parMatrix);

	std::ostream& operator<< (std::ostream& os, const Matrix4& obj); 
}

#endif // BUTTER_MATRIX4_H
