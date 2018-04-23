// Bento includes
#include <bento_base/security.h>

// Library includes
#include "graphics/uniformhandler.h"
#include "graphics/shadermanager.h"

namespace donut
{
	TUniform::TUniform()
	: type(TShaderData::INTEGER)
	, slot("INVALID")
	{
		memcpy(data, 0, data_size());
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
		case TShaderData::INTEGER:
			return 4;
			break;
		case donut::TShaderData::FLOAT:
			return 4;
			break;
		case donut::TShaderData::VEC3:
			return 12;
			break;
		case donut::TShaderData::VEC4:
			return 16;
			break;
		case donut::TShaderData::MAT3:
			return 36;
			break;
		case donut::TShaderData::MAT4:
			return 64;
			break;
		}
	}

	void TUniform::inject(ShaderPipelineObject shader) const
	{
		switch (type)
		{
		case donut::TShaderData::INTEGER:
			ShaderManager::Instance().Inject<int>(shader, reinterpret_cast<const int&>(data), slot);
			break;
		case donut::TShaderData::FLOAT:
			ShaderManager::Instance().Inject<float>(shader, reinterpret_cast<const float&>(data), slot);
			break;
		case donut::TShaderData::VEC3:
			ShaderManager::Instance().Inject<bento::Vector3>(shader, reinterpret_cast<const bento::Vector3&>(data), slot);
			break;
		case donut::TShaderData::VEC4:
			ShaderManager::Instance().Inject<bento::Vector4>(shader, reinterpret_cast<const bento::Vector4&>(data), slot);
			break;
		case donut::TShaderData::MAT3:
			ShaderManager::Instance().Inject<bento::Matrix3>(shader, reinterpret_cast<const bento::Matrix3&>(data), slot);
			break;
		case donut::TShaderData::MAT4:
			ShaderManager::Instance().Inject<bento::Matrix4>(shader, reinterpret_cast<const bento::Matrix4&>(data), slot);
			break;
		}
	}

}