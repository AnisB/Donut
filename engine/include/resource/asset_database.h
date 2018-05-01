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
		, id(UINT64_MAX)
		{
		}

		uint64_t				id;
		bento::DynamicString	name;
		bento::DynamicString	path;
		ResourceType			type;
		bento::Vector<char>		data;
	};

	class TAssetDatabase
	{
	public:
		TAssetDatabase(bento::IAllocator& alloc);
		~TAssetDatabase();

		// Insert an asset into the database
		void insert_asset(const char* name, const char* path, ResourceType type, bento::Vector<char>& data);

		// Request an asset either using its name or id
		const TAsset* request_asset(const char* name) const;
		const TAsset* request_asset(uint64_t id) const;

	public:
		bento::Vector<TAsset> _assets;
	};
}

namespace bento
{
	void pack_type(Vector<char>& buffer, const donut::TAssetDatabase& database);
	bool unpack_type(const char*& stream, donut::TAssetDatabase& database);

	void to_string(DynamicString& str, const donut::TAssetDatabase& database);
}