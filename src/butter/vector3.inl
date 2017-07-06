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

#include <math.h>

namespace donut
{

	// Constructors;
	Vector3 vector3(const double _x, const double _y, const double _z)
	{
		Vector3 out;
		out.x = _x;
		out.y = _y;
		out.z = _z;
		return out;
	}
	Vector3 vector3(const double _v)
	{
		Vector3 out;
		out.x = _v;
		out.y = _v;
		out.z = _v;
		return out;
	}

	// Operators
	Vector3 operator*(const Vector3& _v1, double _factor)
	{
		return vector3(_v1.x*_factor,  _v1.y*_factor, _v1.z*_factor);
	}
	Vector3 operator*(const Vector3& _v1, const Vector3& _v2)
	{
		return vector3(_v1.x*_v2.x,  _v1.y*_v2.y, _v1.z*_v2.z);
	}

	Vector3 operator/(const Vector3& _v1, double _factor)
	{
		return vector3(_v1.x/_factor,  _v1.y/_factor, _v1.z/_factor);
	}

	Vector3 operator+(const Vector3& _v1, const Vector3& _v2)
	{
		return vector3(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z);
	}

	Vector3 operator-(const Vector3& _v1, const Vector3& _v2)
	{
		return vector3(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z);
	}
	Vector3 operator-(const Vector3& _v1)
	{
		return vector3(-_v1.x,  -_v1.y, -_v1.z);
	}
	
	// Cannonic operations
	double dotProd(const Vector3& _v1, const Vector3& _v2)
	{
		return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z;
	}

	Vector3 crossProd(const Vector3& _v1, const Vector3& _v2)
	{
		return vector3(_v1.y*_v2.z - _v1.z * _v2.y, _v1.z*_v2.x - _v1.x * _v2.z, _v1.x*_v2.y - _v1.y * _v2.x);
	}

	double length(const Vector3& _v1)
	{
		return sqrt(_v1.x * _v1.x + _v1.y * _v1.y + _v1.z * _v1.z);
	}

	double length2(const Vector3& _v1)
	{
		return (_v1.x * _v1.x + _v1.y * _v1.y + _v1.z * _v1.z);
	}

	Vector3 normalize(const Vector3& _v1)
	{
		return _v1/length(_v1);
	}
		// Index access
	double& atIndex(Vector3& _val, int _index)
	{
		return _index == 0 ? _val.x : (_index == 1 ? _val.y : _val.z);
	}

	const double& atIndex_Cst(const Vector3& _val, int _index)
	{
		return _index == 0 ? _val.x : (_index == 1 ? _val.y : _val.z);
	}
}