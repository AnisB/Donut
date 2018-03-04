// Library includes
#include "butter/stream.h"


namespace donut
{
	// Stream operator overload
	std::istream& operator>>(std::istream& _stream, bento::Vector2& _val)
	{
		_stream>>_val.x;
		_stream>>_val.y;
		return _stream;
	}

	std::ostream& operator<<(std::ostream& _stream, bento::Vector2& _val)
	{
		_stream<<_val.x;
		_stream<<' ';
		_stream<<_val.y;
		_stream<<' ';
		return _stream;
	}

	std::istream& operator>>(std::istream& _stream, bento::Vector3& _val)
	{
		_stream>>_val.x;
		_stream>>_val.y;
		_stream>>_val.z;
		return _stream;
	}

	std::ostream& operator<<(std::ostream& _stream, bento::Vector3& _val)
	{
		_stream<<_val.x;
		_stream<<' ';
		_stream<<_val.y;
		_stream<<' ';
		_stream<<_val.z;
		_stream<<' ';
		return _stream;
	}

	std::istream& operator>>(std::istream& _stream, bento::Vector4& _val)
	{
		_stream>>_val.x;
		_stream>>_val.y;
		_stream>>_val.z;
		_stream>>_val.w;
		return _stream;
	}

	std::ostream& operator<<(std::ostream& _stream, bento::Vector4& _val)
	{
		_stream<<_val.x;
		_stream<<' ';
		_stream<<_val.y;
		_stream<<' ';
		_stream<<_val.z;
		_stream<<' ';
		_stream<<_val.w;
		_stream<<' ';
		return _stream;
	}

	std::istream& operator>>(std::istream& _stream, bento::Matrix4& _val)
	{
		for(size_t index = 0; index < 16; ++index)
		{
			_stream>>_val.m[index];
		}
		return _stream;
	}

	std::ostream& operator<<(std::ostream& _stream, bento::Matrix4& _val)
	{
		for(size_t index = 0; index < 16; ++index)
		{
			_stream<<_val.m[index];
			_stream<<' ';
		}
		return _stream;
	}
}