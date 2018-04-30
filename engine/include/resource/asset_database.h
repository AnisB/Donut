#pragma once

// Bento includes
#include <bento_collection/dynamic_string.h>

// Internal includes
#include "types.h"

namespace donut
{
	struct TAsset
	{
		ALLOCATOR_BASED;
		TAsset(bento::IAllocator& alloc)
		: name(alloc)
		, path(alloc)
		, type(ResourceType::none)
		, data(alloc)
		{
		}

		bento::DynamicString name;
		bento::DynamicString path;
		ResourceType type;
		bento::Vector<char> data;
	};

	class TAssetDatabase
	{
	public:
		TAssetDatabase(bento::IAllocator& alloc);
		~TAssetDatabase();

		void insert_asset(const char* name, const char* path, ResourceType type, bento::Vector<char>& data);
		bool request_asset(const char* name, TAsset& output_asset);

	public:
		bento::Vector<TAsset> _assets;
	};
}

namespace bento
{
	void pack_type(Vector<char>& buffer, const donut::TAsset& asset);
	void unpack_type(const char*& stream, donut::TAsset& asset);

	void pack_type(Vector<char>& buffer, const donut::TAssetDatabase& database);
	bool unpack_type(const char*& stream, donut::TAssetDatabase& database);
}