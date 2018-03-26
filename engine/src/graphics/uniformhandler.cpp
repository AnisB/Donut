// Bento includes
#include <bento_base/security.h>

// Library includes
#include "graphics/uniformhandler.h"

namespace donut
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