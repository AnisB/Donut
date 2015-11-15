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

#ifndef BUTTER_MATRIX_3
#define BUTTER_MATRIX_3

// Donut inludes
#include "types.h"

// STL includes
#include <iostream>

namespace Donut
{
	// Init functions
	void matrix3(Matrix3& _mat, MatrixInit::Type reset);
	void SetIdentity(Matrix3& _mat);
	void ResetToZero(Matrix3& _mat);

	// Usual functions		
	double Det(Matrix3& _mat);
	void ToTable(const Matrix3& _matrix, float* content);
	Matrix3 Inverse(const Matrix3& parMatrix);

	// Printing functions
	std::ostream& operator<< (std::ostream& os, const Matrix3& obj);
}

#endif //BUTTER_MATRIX_3
