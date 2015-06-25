#pragma once

#include <Reflection_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class IProperty;

			class REFLECTION_EXPORT IPropertiesMap
			{
				public:
					virtual ~IPropertiesMap(){}
					virtual IProperty* getProperty(const char* name) = 0;
			};
		}
	}
}
