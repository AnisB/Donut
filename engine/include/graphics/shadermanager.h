#pragma once

// Library includes
#include "shader.h"
#include "resource/topping_descriptor.h"
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
		ShaderPipelineObject create_shader(const TShaderPipelineDescriptor& shader_pipeline);
		ShaderPipelineObject create_shader(const char* vertex_shader, const char* tess_control_shader, const char* tess_eval_shader, const char* geometry_shader, const char* fragment_shader);

 		// Enables and disables a shader
 		void EnableShader(ShaderPipelineObject parProgram);
 		void DisableShader( );

 		// Data injection
 		template <typename T>
 		void Inject(ShaderPipelineObject parProgram, const T& _value, const char* parName);

 		template <typename T>
 		void InjectV(ShaderPipelineObject parProgram, const T* _value, int _nbVal, const char* parName);
		
		// Inject Material
		void InjectMaterial(ShaderPipelineObject _shader, const TMaterial& _material);


		// Texture binding/unbinding functions
		void BindTex(uint32_t _texID, uint32_t parOffset);
		void BindCubeMap(uint32_t _texID, uint32_t parOffset);
		void UnbindTex(uint32_t parOffset);
		void UnbindCubeMap(uint32_t parOffset);

		// Texture injection function
		void InjectTex(ShaderPipelineObject parProgram, uint32_t _texID, const char* parName, uint32_t parOffset);
		void InjectCubeMap(ShaderPipelineObject parProgram, uint32_t _texID, const char* parName, uint32_t parOffset);

 	private:
 		std::vector<ShaderPipelineObject> _programs;
 	};
 }