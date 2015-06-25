#pragma once

#include <Reflection_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class IPropertyTypeMetaInfo;

			class REFLECTION_EXPORT IProperty
			{
				public:
					virtual ~IProperty(){}
					virtual const char* getName() = 0;
					virtual IPropertyTypeMetaInfo* getTypeInfo() = 0;
			};
		}
	}
}
