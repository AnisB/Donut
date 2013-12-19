#ifndef MATRIX_4
#define MATRIX_4

#include <math/vector4.h>
#include <math/vector3.h>
#include <math/vec.h>


class Vector4;

namespace MatrixInit
{
	enum Type
	{
		Zero,
		Identity,
		None
	};
}

class Matrix4
{
	public:
		Matrix4(MatrixInit::Type reset = MatrixInit::Zero);
		Matrix4(const Matrix4& parMatrix);
		~Matrix4();
		
		void setIdentity();
		void resetToZero();
		Vector3 getTranslate();
		Vector3 xAxis();
		Vector3 yAxis();
		Vector3 zAxis();
		
		double det() const;
		static Matrix4 inverse(const Matrix4& parMatrix);
		static Matrix4 translate(const Vector4& parVector);
		static Matrix4 translate(const TVec3& parVector);
		static Matrix4 translate(const Vector3& parVector);
		// TODO 
		// =>
		static Matrix4 rotate(double parAngle, const Vector3& parAxis);
		void toTable(float* content) const;
		void AsPerspective(float parFovy, float parAspect, float parNear, float parFar);

		static Matrix4 rotateXAxis(double parAngle);
		static Matrix4 rotateYAxis(double parAngle);
		static Matrix4 rotateZAxis(double parAngle);

		Vector4 operator*(const Vector4& parFactor) const;
		Matrix4 operator*(const Matrix4& parMatrix) const;
		Matrix4& operator=(const Matrix4& parMatrix);

		
	public:
		double ** m;
};
std::ostream& operator<< (std::ostream& os, const Matrix4& obj); 

#endif //MATRIX_4
