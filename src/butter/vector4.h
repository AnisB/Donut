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
#ifndef BUTTER_VECTOR4_H
#define BUTTER_VECTOR4_H

// donut includes
#include "types.h"

namespace donut
{
	// inline methods
		// Constructors
	inline Vector4 vector4(const double _x, const double _y, const double _z, const double _w);
	inline Vector4 vector4(const double _v);

		// Operators
	inline Vector4 operator*(const Vector4& _v1, double parFactor);
	inline Vector4 operator/(const Vector4& _v1, double parFactor);
	inline Vector4 operator+(const Vector4& _v1, const Vector4& _v2);
	inline Vector4 operator-(const Vector4& _v1, const Vector4& _v2);

		// Cannonic operations
	inline double dotProd(const Vector4& _v1, const Vector4& _v2);
	inline Vector4 crossProd(const Vector4& _v1, const Vector4& _v2);
	inline double length(const Vector4& _v1);
	inline double length2(const Vector4& _v1);
	inline Vector4 normalize(const Vector4& _vec);

	// Default values;
	extern const Vector4 v4_ZERO;
	extern const Vector4 v4_X;
	extern const Vector4 v4_Y;
	extern const Vector4 v4_Z;
	extern const Vector4 v4_W;
}

#include "vector4.inl"

#endif // BUTTER_VECTOR4_H
