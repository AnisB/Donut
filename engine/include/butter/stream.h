#ifndef STREAM_BUTTER_H
#define STREAM_BUTTER_H

// Library includes
#include "bento_math/types.h"

// External includes
#include <iostream>

namespace donut 
{
	// Stream operator overload
	std::istream& operator>>(std::istream& _stream, bento::Vector2& _val);
	std::ostream& operator<<(std::ostream& _stream, bento::Vector2& _val);

	std::istream& operator>>(std::istream& _stream, bento::Vector3& _val);
	std::ostream& operator<<(std::ostream& _stream, bento::Vector3& _val);

	std::istream& operator>>(std::istream& _stream, bento::Vector4& _val);
	std::ostream& operator<<(std::ostream& _stream, bento::Vector4& _val);

	std::istream& operator>>(std::istream& _stream, bento::Matrix4& _val);
	std::ostream& operator<<(std::ostream& _stream, bento::Matrix4& _val);
}

#endif // STREAM_BUTTER_H