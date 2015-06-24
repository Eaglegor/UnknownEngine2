#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class IProperty;

			class IPropertiesMap
			{
				public:
					virtual ~IPropertiesMap(){}
					virtual IProperty* getProperty(const char* name) = 0;
			};
		}
	}
}
