#ifndef STREAM_BUTTER_H
#define STREAM_BUTTER_H

// Library includes
#include "types.h"

// External includes
#include <iostream>

namespace Donut 
{
	// Stream operator overload
	std::istream& operator>>(std::istream& _stream, Vector2& _val);
	std::ostream& operator<<(std::ostream& _stream, Vector2& _val);

	std::istream& operator>>(std::istream& _stream, Vector3& _val);
	std::ostream& operator<<(std::ostream& _stream, Vector3& _val);

	std::istream& operator>>(std::istream& _stream, Vector4& _val);
	std::ostream& operator<<(std::ostream& _stream, Vector4& _val);

	std::istream& operator>>(std::istream& _stream, Matrix4& _val);
	std::ostream& operator<<(std::ostream& _stream, Matrix4& _val);	
}

#endif // STREAM_BUTTER_H