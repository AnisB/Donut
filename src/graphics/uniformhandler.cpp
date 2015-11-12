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


// Library includes
#include "uniformhandler.h"
#include "graphics/shadermanager.h"
#include "base/security.h"

namespace Donut
{
	TUniformHandler::TUniformHandler()
	: m_uniform(nullptr)
	{

	}
	TUniformHandler::~TUniformHandler()
	{
		if(m_uniform)
		{
			delete m_uniform;
		}
	}
	
	TUniformHandler::TUniformHandler(TUniformHandler&& _uniformHandler)
	{
		m_uniform = _uniformHandler.m_uniform;
		_uniformHandler.m_uniform = nullptr;
	}

	TUniformHandler& TUniformHandler::operator=(const TUniformHandler& _uniformHandler)
	{
		if(_uniformHandler.m_uniform)
			m_uniform = _uniformHandler.m_uniform->Clone();
		return *this;
	}

	TUniformHandler& TUniformHandler::operator=(TUniformHandler&& _uniformHandler)
	{
		m_uniform = _uniformHandler.m_uniform;
		_uniformHandler.m_uniform = nullptr;
		return *this;
	}

	TUniformHandler::TUniformHandler(const TUniformHandler& _uniformHandler)
	{
		m_uniform = _uniformHandler.m_uniform->Clone();
	}

	TShaderData::Type TUniformHandler::GetType() const
	{
		if(m_uniform)
		{
			return m_uniform->type;
		}
		return TShaderData::TYPE;
	}

	// Injecting an uniform variable
	void TUniformHandler::Inject(const TShader& _shader) const
	{
		TShaderData::Type val = m_uniform->type;

		switch (val)
		{
			case TShaderData::INTEGER:
			{
				TUniform<int>* convert = static_cast<TUniform<int>*>(m_uniform);
				ShaderManager::Instance().Inject<int>(_shader, convert->value,m_uniform->name);
			}
			break;
			case TShaderData::FLOAT:
			{
				TUniform<float>* convert = static_cast<TUniform<float>*>(m_uniform);
				ShaderManager::Instance().Inject<float>(_shader, convert->value,m_uniform->name);
			}
			break;
			case TShaderData::MAT4:
			{
				TUniform<Matrix4>* convert = static_cast<TUniform<Matrix4>*>(m_uniform);
				ShaderManager::Instance().Inject<Matrix4>(_shader, convert->value,m_uniform->name);
			}
			break;
			case TShaderData::VEC3:
			{
				TUniform<Vector3>* convert = static_cast<TUniform<Vector3>*>(m_uniform);
				ShaderManager::Instance().Inject<Vector3>(_shader, convert->value,m_uniform->name);
			}
			break;
			case TShaderData::VEC4:
			{
				TUniform<Vector4>* convert = static_cast<TUniform<Vector4>*>(m_uniform);
				ShaderManager::Instance().Inject<Vector4>(_shader, convert->value,m_uniform->name);
			}
			break;
			case TShaderData::MAT3:
			{
				TUniform<Matrix3>* convert = static_cast<TUniform<Matrix3>*>(m_uniform);
				ShaderManager::Instance().Inject<Matrix3>(_shader, convert->value,m_uniform->name);
			}
			break;
			default:
				ASSERT_FAIL_MSG("Unsupported uniform type "<<val);
		}
	}
}