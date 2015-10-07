#pragma once

#include "ComponentType.h"
#include <Utils/Common/String.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			using Utils::Common::String;

			struct ComponentDesc
			{
				String name;
				ComponentType type;
			};
		}
	}
}