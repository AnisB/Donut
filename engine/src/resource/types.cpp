// Internal includes
#include "resource/types.h"

namespace donut
{
	const char* resource_type_to_string(ResourceType type)
	{
		switch (type)
		{
			case ResourceType::texture:
			{
				return "texture";
			}
			break;
			case ResourceType::topping:
			{
				return "topping";
			}
			break;
			case ResourceType::sugar:
			{
				return "sugar";
			}
			break;
			case ResourceType::shader:
			{
				return "shader";
			}
			break;
			case ResourceType::pipeline:
			{
				return "pipeline";
			}
			break;
			case ResourceType::flour:
			{
				return "pipeline";
			}
			break;
			case ResourceType::egg:
			{
				return "egg";
			}
			break;
			default:
				return "none";
		};
	}
}