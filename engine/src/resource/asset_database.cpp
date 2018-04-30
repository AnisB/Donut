// Bento includes
#include "bento_base/stream.h"

// Internal includes
#include "resource/asset_database.h"

namespace donut
{
	const uint32_t DATABASE_VERSION = 1;

	TAssetDatabase::TAssetDatabase(bento::IAllocator& alloc)
	: _assets(alloc)
	{

	}

	TAssetDatabase::~TAssetDatabase()
	{

	}

	void TAssetDatabase::insert_asset(const char* name, const char* path, ResourceType type, bento::Vector<char>& data)
	{
		// Compute the new index
		uint32_t new_asset_idx = _assets.size();
		
		// Create and fetch the new asset		
		_assets.resize(new_asset_idx + 1);

		// Assign the data of to the asset
		TAsset& asset = _assets[new_asset_idx];
		asset.name = name;
		asset.path = path;
		asset.type = type;
		asset.data = data;
	}

	bool TAssetDatabase::request_asset(const char* name, TAsset& output_asset)
	{
		// Fetch the asset count
		uint32_t num_assets = _assets.size();

		for(uint32_t asset_idx = 0; asset_idx < num_assets; ++asset_idx)
		{
			TAsset& current_asset = _assets[asset_idx];
			if(current_asset.name == name)
			{
				output_asset = current_asset;
				return true;
			}
		}

		return false;
	}
}

namespace bento
{
	void pack_type(Vector<char>& buffer, const donut::TAsset& asset)
	{
		pack_type(buffer, asset.name);
		pack_type(buffer, asset.path);
		pack_bytes(buffer, asset.type);
		pack_vector_bytes(buffer, asset.data);
	}

	void unpack_type(const char*& stream, donut::TAsset& asset)
	{
		unpack_type(stream, asset.name);
		unpack_type(stream, asset.path);
		unpack_bytes(stream, asset.type);
		unpack_vector_bytes(stream, asset.data);
	}

	void pack_type(Vector<char>& buffer, const donut::TAssetDatabase& database)
	{
		pack_bytes(buffer, donut::DATABASE_VERSION);
		pack_vector_types(buffer, database._assets);
	}

	bool unpack_type(const char*& stream, donut::TAssetDatabase& database)
	{
		// Read the version
		uint32_t database_version;
		unpack_bytes(stream, database_version);

		// Stop if this does not match the current version
		if (database_version != donut::DATABASE_VERSION) return false;
		unpack_vector_bytes(stream, database._assets);
		return true;
	}
}