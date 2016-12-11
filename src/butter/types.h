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
#ifndef BUTTER_TYPES_H
#define BUTTER_TYPES_H

namespace Donut
{
	// Vector types
	// doubles
	struct Vector2
	{
		double x,y;
	};
	struct Vector3
	{
		double x,y,z;
	};
	struct Vector4
	{
		double x,y,z,w;
	};

	// Int
	struct IVector2
	{
		int x,y;
	};
	struct IVector3
	{
		int x,y,z;
	};
	struct IVector4
	{
		int x,y,z,w;
	};

	// Matrix
	namespace MatrixInit
	{
		enum Type
		{
			Zero,
			Identity
		};
	}
	
	struct Matrix3
	{
		inline Matrix3(){}
		Matrix3(const Matrix3& _mat);
		Matrix3& operator=(const Matrix3 _mat);
		double m[9];
	};
	
	struct Matrix4
	{
		inline Matrix4(){}
		Matrix4(const Matrix4& _mat);
		Matrix4& operator=(const Matrix4 _mat);
		double m[16];
	};
}

#endif // BUTTER_TYPES_H