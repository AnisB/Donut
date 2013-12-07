#ifndef MATRIX_3
#define MATRIX_3

#include "math/vector3.h"
#include <iostream>


class Vector3;
class Matrix3
{
	public:
		Matrix3();
		Matrix3(const Matrix3& parMatrix);
		~Matrix3();
		
		void setIdentity();
		void resetToZero();
		
		double det() const;
		static Matrix3 inverse(const Matrix3& parMatrix);
		Vector3 operator*=(const Vector3& parFactor);
		Matrix3& operator=(const Matrix3& parMatrix);
		
	public:
		double ** m;
};
std::ostream& operator<< (std::ostream& os, const Matrix3& obj);

#endif //MATRIX_3
