#ifndef BUTTER_MATRIX_3
#define BUTTER_MATRIX_3

#include "types.h"
#include <iostream>

namespace Donut
{
	void SetIdentity(Matrix3& _mat);
	void ResetToZero(Matrix3& _mat);
		
	double Det(Matrix3& _mat);
	Matrix3 Inverse(const Matrix3& parMatrix);
	std::ostream& operator<< (std::ostream& os, const Matrix3& obj);
}
#endif //BUTTER_MATRIX_3
