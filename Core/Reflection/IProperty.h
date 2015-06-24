#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class IPropertyTypeMetaInfo;

			class IProperty
			{
				public:
					virtual ~IProperty(){}
					virtual const char* getName() = 0;
					virtual IPropertyTypeMetaInfo* getTypeInfo() = 0;
			};
		}
	}
}
