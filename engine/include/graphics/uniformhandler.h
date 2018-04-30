#pragma once

// Bento includes
#include <bento_base/security.h>

// Libray includes
#include "graphics/shaderdata.h"

// STL includes
#include <string>

namespace donut
{
	struct TUniform
	{
		TUniform();
		TUniform(const TUniform& uniform);

		template <typename T>
		void set_data(TShaderDataType _type, const char* slot_name, const T& v)
		{
			type = _type;
			slot = slot_name;
			memcpy(data, (const unsigned char*)&v, data_size());
		}

		template <typename T>
		void get_data(T& v)
		{
			v = reinterpret_cast<const T&>(data);
		}

		uint8_t data_size() const;
		void inject(ShaderPipelineObject _shader) const;

	    TShaderDataType	type;
		std::string			slot;
		uint64_t			data[8];
	};
}
