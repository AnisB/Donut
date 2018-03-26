// Bento includes
#include <bento_base/security.h>

// Library includes
#include "resource/shaderfilehandler.h"

namespace donut
{
	static TShaderFileID s_shaderCounter = 0;
	// Init and uninit
	TShaderFileHandler::TShaderFileHandler()
	{
		// Nothing to do
	}
		
	TShaderFileHandler::~TShaderFileHandler()
	{
		// Nothing to do
	}

	// Methods
	TShaderFileID TShaderFileHandler::RegisterShaderFile(const STRING_TYPE& _shaderFile)
	{
		auto result = m_shaderKeys.find(_shaderFile);
		if(result == m_shaderKeys.end())
		{
			m_shaderKeys[_shaderFile] = s_shaderCounter;
			m_inverseShaderKeys[s_shaderCounter] = _shaderFile;
			return s_shaderCounter++; // The ++ operator returns a copy pre-incrementation
		}
		else
		{
			return result->second;
		}
	}

	const STRING_TYPE& TShaderFileHandler::GetShaderFile(const TShaderFileID& _shaderID)
	{
		auto result = m_inverseShaderKeys.find(_shaderID);
		if(result == m_inverseShaderKeys.end())
		{
			assert_msg(result != m_inverseShaderKeys.end(), "Shader was required but never registered");
		}
		return result->second;
	}

	bool TShaderFileHandler::IsRegistered(const STRING_TYPE& _shaderFile)
	{
		auto result = m_shaderKeys.find(_shaderFile);
		return (result != m_shaderKeys.end());
	}
}