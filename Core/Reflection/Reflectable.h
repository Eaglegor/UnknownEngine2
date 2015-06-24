#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class ITypeMetaInfo;
			class IPropertiesMap;

			class Reflectable
			{
				public:
					virtual ~Reflectable(){}
					virtual ITypeMetaInfo* getTypeMetaInfo() = 0;
					virtual IPropertiesMap* getProperties() = 0;
			};
		}
	}
}
