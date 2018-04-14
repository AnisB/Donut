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