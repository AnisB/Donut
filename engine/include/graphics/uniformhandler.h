#pragma once

// Bento includes
#include <bento_base/security.h>

// Libray includes
#include "graphics/shader.h"
#include "resource/common.h"
#include "graphics/shadermanager.h"

// STL includes
#include <string>

namespace donut
{
	namespace TShaderData
	{
	    enum Type
	    {
	        INTEGER = 0,
	        FLOAT = 1,
	        VEC3 = 2,
	        VEC4 = 3,
	        MAT3 = 4,
	        MAT4 = 5,
	        TYPE = 6
	    };
	}

	struct TUniformGeneric
	{
		// Data constructor
		TUniformGeneric(TShaderData::Type _type, const STRING_TYPE& _name)
		: type(_type)
		, name (_name)
		{
		}
		// Copy constructor		
		TUniformGeneric(const TUniformGeneric& _uniformGeneric)
		: type(_uniformGeneric.type)
		, name (_uniformGeneric.name)
		{

		}
		// Virtual destructor
		virtual ~TUniformGeneric() {}

		// Clone function, must be overloaded
		virtual TUniformGeneric* Clone() = 0;
		virtual void Inject(const TShader& _shader) = 0;
		// Data
	    TShaderData::Type type;
		STRING_TYPE name;
	};

	template <typename T>
	struct TUniform : public TUniformGeneric
	{
		TUniform(TShaderData::Type _type, const STRING_TYPE& _name, const T& _value)
		: TUniformGeneric(_type, _name)
		, value(_value)
		{

		}
		TUniform(const TUniform& _uniform)
		: TUniformGeneric(_uniform.type, _uniform.name)
		, value (_uniform.value)
		{

		}
		TUniformGeneric* Clone()
		{
			return (new TUniform<T> (type, name, value));
		}
		
		void Inject(const TShader& _shader)
		{
			ShaderManager::Instance().Inject<T>(_shader, value, name);
		}

		T value;
	    const T& GetValue() { return value;}
	};

	class TUniformHandler
	{
	public:
		TUniformHandler();
		TUniformHandler(const TUniformHandler& _uniform);
		TUniformHandler(TUniformHandler&& _uniform);
		~TUniformHandler();

		// Setting value
		template <typename T>
		void SetValue(TShaderData::Type _type, const STRING_TYPE& _name, const T& _value);
		
		template <typename T>
		T& GetValue();

		// InjectValue
		void Inject(const TShader& _shader) const;
		TShaderData::Type GetType() const;
		TUniformHandler& operator=(const TUniformHandler& _val);
		TUniformHandler& operator=(TUniformHandler&& _val);

	private:
		TUniformGeneric* m_uniform;
	};

	template <typename T>
	void TUniformHandler::SetValue(TShaderData::Type _type, const STRING_TYPE& _name, const T& _value)
	{
		if(m_uniform)
		{
			if(m_uniform->type != _type)
			{
				delete m_uniform;
				m_uniform = new TUniform<T>(_type, _name, _value);
			}
			else
			{
				static_cast<TUniform<T>* >(m_uniform)->value = _value;
			}
		}
		else
		{
			m_uniform = new TUniform<T>(_type, _name, _value);
		}

	}
	template <typename T>
	T& TUniformHandler::GetValue()
	{
		TUniform<T>* casted = static_cast<TUniform<T>*>(m_uniform);
		assert(casted != nullptr);
		return casted->value;
	}
}
