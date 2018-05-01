// Bento includes
#include <bento_base/security.h>

// Library includes
#include "graphics/uniformhandler.h"
#include "graphics/shadermanager.h"

namespace donut
{
	TUniform::TUniform()
	: type(TShaderDataType::INTEGER)
	, slot("INVALID")
	{
		memset(data, 0, data_size());
	}

	TUniform::TUniform(const TUniform& uniform)
	: type(uniform.type)
	, slot(uniform.slot)
	{
		memcpy(data, uniform.data, sizeof(uint64_t) * 8);
	}

	uint8_t TUniform::data_size() const
	{
		switch (type)
		{
		case TShaderDataType::INTEGER:
			return 4;
			break;
		case donut::TShaderDataType::FLOAT:
			return 4;
			break;
		case donut::TShaderDataType::VEC3:
			return 12;
			break;
		case donut::TShaderDataType::VEC4:
			return 16;
			break;
		case donut::TShaderDataType::MAT3:
			return 36;
			break;
		case donut::TShaderDataType::MAT4:
			return 64;
			break;
		}
		return 0;
	}

	void TUniform::inject(ShaderPipelineObject shader) const
	{
		switch (type)
		{
		case donut::TShaderDataType::INTEGER:
			ShaderManager::Instance().Inject<int>(shader, reinterpret_cast<const int&>(data), slot.c_str());
			break;
		case donut::TShaderDataType::FLOAT:
			ShaderManager::Instance().Inject<float>(shader, reinterpret_cast<const float&>(data), slot.c_str());
			break;
		case donut::TShaderDataType::VEC3:
			ShaderManager::Instance().Inject<bento::Vector3>(shader, reinterpret_cast<const bento::Vector3&>(data), slot.c_str());
			break;
		case donut::TShaderDataType::VEC4:
			ShaderManager::Instance().Inject<bento::Vector4>(shader, reinterpret_cast<const bento::Vector4&>(data), slot.c_str());
			break;
		case donut::TShaderDataType::MAT3:
			ShaderManager::Instance().Inject<bento::Matrix3>(shader, reinterpret_cast<const bento::Matrix3&>(data), slot.c_str());
			break;
		case donut::TShaderDataType::MAT4:
			ShaderManager::Instance().Inject<bento::Matrix4>(shader, reinterpret_cast<const bento::Matrix4&>(data), slot.c_str());
			break;
		}
	}

}