#ifndef RENDER_DISTPATCHER_H
#define RENDER_DISTPATCHER_H

// External includes
#include <map>
namespace Donut
{

	// Foward declare
	class TGeometry;
	class TMaterial;
	class TUniformHandler;

	struct TMeshRenderStruct
	{
		TMaterial* mat;
		TGeometry* geo;
		std::map<std::string, TUniformHandler> data;
	};

	// This class is able to take render calls and the process them
	class TDispatcher
	{
	public:
		TDispatcher()
		{

		}

		~TDispatcher()
		{

		}
	};
}

#endif // RENDER_DISTPATCHER_H