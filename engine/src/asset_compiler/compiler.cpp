// Bento includes
#include <bento_base/log.h>
#include <bento_tools/file_system.h>

// Internal includes includes
#include "asset_compiler/compiler.h"
#include "asset_compiler/egg_helpers.h"
#include "asset_compiler/flour_helpers.h"
#include "asset_compiler/pipeline_helpers.h"
#include "asset_compiler/topping_helpers.h"
#include "asset_compiler/texture_helpers.h"
#include "asset_compiler/compiler_options.h"
#include "asset_compiler/asset_database_helpers.h"
#include "asset_compiler/shader_source_helpers.h"
#include "asset_compiler/sugar_helpers.h"

namespace donut {
namespace asset_compiler {

	bool compile(const TCompilerOptions& compiler_option, TAssetDatabase& asset_db)
	{
		// Flag that tracks the compilation failure or success
		bool compilation_result = true;

		bento::IAllocator& current_allocator = *bento::common_allocator();

		// Length of the source dir string (plus the slash)
		uint32_t source_dir_length = compiler_option._source_dir.size() + 1;

		// Collect all the texture files
		bento::Vector<bento::DynamicString> textures(current_allocator);
		bento::file_system::collect_files_with_extension(compiler_option._source_dir.c_str(), "jpg", textures);
		bento::file_system::collect_files_with_extension(compiler_option._source_dir.c_str(), "png", textures);
		bento::file_system::collect_files_with_extension(compiler_option._source_dir.c_str(), "bmp", textures);
		bento::file_system::collect_files_with_extension(compiler_option._source_dir.c_str(), "tga", textures);

		// Loop through the textures
		uint32_t num_textures = textures.size();
		for (uint32_t tex_idx = 0; tex_idx < num_textures; ++tex_idx)
		{
			// Get the path of the texture
			const bento::DynamicString& tex_path = textures[tex_idx];

			// Asset compile the texture
			donut::TTexture target_texture(current_allocator);
			bool res = donut::read_texture(tex_path.c_str(), target_texture);

			if (res)
			{
				// Insert the texture to the database
				bento::Vector<char> data(current_allocator);
				bento::pack_type(data, target_texture);
				asset_db.insert_asset(tex_path.c_str() + source_dir_length, tex_path.c_str() + source_dir_length, donut::ResourceType::texture, data);
			}
			else
			{
				bento::default_logger()->log(bento::LogLevel::error, "ASSET_COMPILER", "Failed to compile texture");
			}
		}

		// Collect and asset compile all the shader sources
		bento::Vector<bento::DynamicString> shaders(current_allocator);
		bento::file_system::collect_files_with_extension(compiler_option._source_dir.c_str(), "glsl", shaders);

		uint32_t num_shaders = shaders.size();
		for (uint32_t shader_idx = 0; shader_idx < num_shaders; ++shader_idx)
		{
			// Get the path of the shader
			const bento::DynamicString& shader_path = shaders[shader_idx];

			// Holder of the compiled asset
			donut::TShaderSource shader_source(current_allocator);
			bool res = donut::read_shader_source(shader_path.c_str(), shader_source);

			if (res)
			{
				// Insert the texture to the database
				bento::Vector<char> data(current_allocator);
				bento::pack_type(data, shader_source);
				asset_db.insert_asset(shader_path.c_str() + source_dir_length, shader_path.c_str() + source_dir_length, donut::ResourceType::shader, data);
			}
			else
			{
				compilation_result = false;
				bento::default_logger()->log(bento::LogLevel::error, "ASSET_COMPILER", "Failed to compile shader");
			}
		}

		// Collect and asset compile all the sugar sources
		bento::Vector<bento::DynamicString> sugars(current_allocator);
		bento::file_system::collect_files_with_extension(compiler_option._source_dir.c_str(), "sugar", sugars);

		uint32_t num_sugars = sugars.size();
		for (uint32_t sugar_idx = 0; sugar_idx < num_sugars; ++sugar_idx)
		{
			// Get the path of the shader
			const bento::DynamicString& sugar_path = sugars[sugar_idx];

			// Holder of the compiled asset
			donut::TSugarDescriptor sugar_descriptor(current_allocator);
			bool res = donut::read_sugar(sugar_path.c_str(), sugar_descriptor);

			if (res)
			{
				// Insert the texture to the database
				bento::Vector<char> data(current_allocator);
				bento::pack_type(data, sugar_descriptor);
				asset_db.insert_asset(sugar_descriptor._name.c_str(), sugar_path.c_str() + source_dir_length, donut::ResourceType::sugar, data);
			}
			else
			{
				compilation_result = false;
				bento::default_logger()->log(bento::LogLevel::error, "ASSET_COMPILER", "Failed to compile sugar");
			}
		}

		// Collect and asset compile all the topping sources
		bento::Vector<bento::DynamicString> toppings(current_allocator);
		bento::file_system::collect_files_with_extension(compiler_option._source_dir.c_str(), "topping", toppings);

		uint32_t num_toppings = toppings.size();
		for (uint32_t topping_idx = 0; topping_idx < num_toppings; ++topping_idx)
		{
			// Get the path of the shader
			const bento::DynamicString& topping_path = toppings[topping_idx];

			// Holder of the compiled asset
			donut::TToppingDescriptor stopping_descriptor(current_allocator);
			bool res = donut::read_topping(topping_path.c_str(), stopping_descriptor);

			if (res)
			{
				// Insert the texture to the database
				bento::Vector<char> data(current_allocator);
				bento::pack_type(data, stopping_descriptor);
				asset_db.insert_asset(stopping_descriptor.name.c_str(), topping_path.c_str() + source_dir_length, donut::ResourceType::topping, data);
			}
			else
			{
				compilation_result = false;
				bento::default_logger()->log(bento::LogLevel::error, "ASSET_COMPILER", "Failed to compile topping");
			}
		}

		// Collect and asset compile all the pipeline sources
		bento::Vector<bento::DynamicString> pipelines(current_allocator);
		bento::file_system::collect_files_with_extension(compiler_option._source_dir.c_str(), "pipeline", pipelines);

		uint32_t num_pipelines = pipelines.size();
		for (uint32_t pipeline_idx = 0; pipeline_idx < num_pipelines; ++pipeline_idx)
		{
			// Get the path of the shader
			const bento::DynamicString& pipeline_path = pipelines[pipeline_idx];

			// Holder of the compiled asset
			donut::TPipelineDescriptor pipeline_descriptor(current_allocator);
			bool res = donut::read_pipeline(pipeline_path.c_str(), pipeline_descriptor);

			if (res)
			{
				// Insert the texture to the database
				bento::Vector<char> data(current_allocator);
				bento::pack_type(data, pipeline_descriptor);
				asset_db.insert_asset(pipeline_descriptor.name.c_str(), pipeline_path.c_str() + source_dir_length, donut::ResourceType::pipeline, data);
			}
			else
			{
				compilation_result = false;
				bento::default_logger()->log(bento::LogLevel::error, "ASSET_COMPILER", "Failed to compile pipeline");
			}
		}

		// Collect and asset compile all the pipeline sources
		bento::Vector<bento::DynamicString> flours(current_allocator);
		bento::file_system::collect_files_with_extension(compiler_option._source_dir.c_str(), "flour", flours);

		uint32_t num_flours = flours.size();
		for (uint32_t flour_idx = 0; flour_idx < num_flours; ++flour_idx)
		{
			// Get the path of the shader
			const bento::DynamicString& flour_path = flours[flour_idx];

			// Holder of the compiled asset
			donut::TFlourDescriptor flour_descriptor(current_allocator);
			bool res = donut::read_flour(flour_path.c_str(), flour_descriptor);

			if (res)
			{
				// Insert the texture to the database
				bento::Vector<char> data(current_allocator);
				bento::pack_type(data, flour_descriptor);
				asset_db.insert_asset(flour_descriptor.name.c_str(), flour_path.c_str() + source_dir_length, donut::ResourceType::flour, data);
			}
			else
			{
				compilation_result = false;
				bento::default_logger()->log(bento::LogLevel::error, "ASSET_COMPILER", "Failed to compile flour");
			}
		}

		// Collect and asset compile all the pipeline sources
		bento::Vector<bento::DynamicString> geometries(current_allocator);
		bento::file_system::collect_files_with_extension(compiler_option._source_dir.c_str(), "obj", geometries);

		uint32_t num_geometries = geometries.size();
		for (uint32_t geo_idx = 0; geo_idx < num_geometries; ++geo_idx)
		{
			// Get the path of the shader
			const bento::DynamicString& geo_path = geometries[geo_idx];

			// Holder of the compiled asset
			donut::TEgg egg(current_allocator);
			bool res = donut::read_egg(geo_path.c_str(), egg);

			if (res)
			{
				// Insert the texture to the database
				bento::Vector<char> data(current_allocator);
				bento::pack_type(data, egg);
				asset_db.insert_asset(geo_path.c_str() + source_dir_length, geo_path.c_str() + source_dir_length, donut::ResourceType::egg, data);
			}
			else
			{
				compilation_result = false;
				bento::default_logger()->log(bento::LogLevel::error, "ASSET_COMPILER", "Failed to compile egg");
			}
		}

		return compilation_result;
	}

	void write(const TCompilerOptions& options, const TAssetDatabase& asset_db)
	{
		// Write the database and the debug file to the target_file
		bento::DynamicString output_database_path(*bento::common_allocator());
		output_database_path += options._output_dir;
		output_database_path += "/asset_database";
		donut::write_database(output_database_path.c_str(), asset_db);
		donut::write_database_debug(output_database_path.c_str(), asset_db);
	}
}
}