#pragma once

#include "IPropertyTypeMetaInfo.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			template<typename T>
			class PropertyTypeMetaInfo
			{
				public:
					// Only specializations are allowed to be used
					PropertyTypeMetaInfo() = delete;
			};
		}
	}
}
