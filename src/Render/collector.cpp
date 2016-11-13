// Library include
#include "base/macro.h"
#include "collector.h"
#include "graphics/material.h"
#include "resource/resourcemanager.h"
#include "resource/toppingloader.h"

namespace Donut
{
	TCollector::TCollector()
	{
		// Nothing to do
	}

	TCollector::~TCollector()
	{
		// Nothing to do
	}

	// Clears the render request queue
	void TCollector::Clear()
	{
		m_requests.clear();
	}
}