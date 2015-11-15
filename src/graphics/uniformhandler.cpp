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
		m_uniform->Inject(_shader);
	}
}