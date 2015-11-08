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
		TUniformGeneric(TShaderData::Type _type, const std::string& _name)
		: type(_type)
		, name (_name)
		{

		}
		std::string name;
	    TShaderData::Type type;
	};

	template <typename T>
	struct TUniform : public TUniformGeneric
	{
		TUniform(TShaderData::Type _type, const std::string& _name, const T& _value)
		: TUniformGeneric(_type, _name)
		, value(_value)
		{

		}
		T value;
	    const T& GetValue() { return value;}
	};

	class TUniformHandler
	{
	public:
		TUniformHandler();
		TUniformHandler(const TUniformHandler& _uniform);
		~TUniformHandler();

		// Setting value
		template <typename T>
		void SetValue(TShaderData::Type _type, const std::string& _name, const T& _value);
		// InjectValue
		void Inject(const TShader& _shader) const;
		TShaderData::Type GetType() const;

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
}

#endif  // UNIFORM_HANDLER_GRAPHICS_DONUT

