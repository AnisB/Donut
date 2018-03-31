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

#pragma once

// Library includes
#include "shader.h"

#include "base/singleton.h"

// Bento includes
#include <bento_math/Vector3.h>
#include <bento_math/Matrix4.h>

// STL includes
#include <unordered_set>

namespace donut
{
	// Foward declare 
	struct TMaterial;


	class ShaderManager : public Singleton<ShaderManager>
	{

	public:
		// Init && uninit
		ShaderManager();
		virtual ~ShaderManager();

 		// Creates a shader in GPU memory
 		bool CreateShader(TShader& parShader);

 		// Enables and disables a shader
 		void EnableShader(const TShader& parProgram);
 		void DisableShader( );

 		// Data injection
 		template <typename T>
 		void Inject(const TShader& parProgram, const T& _value, const STRING_TYPE& parName);

 		template <typename T>
 		void InjectV(const TShader& parProgram, const T* _value, int _nbVal, const STRING_TYPE& parName);
		
		// Inject Material
		void InjectMaterial(const TShader& _shader, const TMaterial& _material);


		// Texture binding/unbinding functions
		void BindTex(uint32_t _texID, uint32_t parOffset);
		void BindCubeMap(uint32_t _texID, uint32_t parOffset);
		void UnbindTex(uint32_t parOffset);
		void UnbindCubeMap(uint32_t parOffset);

		// Texture injection function
		void InjectTex(const TShader& parProgram, uint32_t _texID, const STRING_TYPE& parName, uint32_t parOffset);
		void InjectCubeMap(const TShader& parProgram, uint32_t _texID, const STRING_TYPE& parName, uint32_t parOffset);
 	private:
 		std::unordered_set<TShader,TShaderHasher> FPrograms;
 	};
 }