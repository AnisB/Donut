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
#ifndef UNIFORM_HANDLER_GRAPHICS_DONUT
#define UNIFORM_HANDLER_GRAPHICS_DONUT
// Libray includes
#include "graphics/shader.h"
#include "resource/common.h"
#include "graphics/shadermanager.h"

// STL includes
#include <string>

namespace Donut
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
		TUniformGeneric(TShaderData::Type _type, const std::string& _name)
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
		std::string name;
	};

	template <typename T>
	struct TUniform : public TUniformGeneric
	{
		TUniform(TShaderData::Type _type, const std::string& _name, const T& _value)
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
		void SetValue(TShaderData::Type _type, const std::string& _name, const T& _value);
		
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
	void TUniformHandler::SetValue(TShaderData::Type _type, const std::string& _name, const T& _value)
	{
		if(m_uniform)
			delete m_uniform;
		m_uniform = new TUniform<T>(_type, _name, _value);
	}
	template <typename T>
	T& TUniformHandler::GetValue()
	{
		TUniform<T>* casted = static_cast<TUniform<T>*>(m_uniform);
		ASSERT_NO_RELEASE(casted != nullptr);
		return casted->value;
	}
}

#endif  // UNIFORM_HANDLER_GRAPHICS_DONUT

