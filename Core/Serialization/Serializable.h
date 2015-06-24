#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class IPropertiesMap;
			class ITypeMetaInfo;
		}

		namespace Serialization
		{
			class Serializable
			{
				public:
					virtual ~Serializable(){}
					virtual Reflection::IPropertiesMap* getProperties() = 0;
					virtual Reflection::ITypeMetaInfo* getTypeMetaInfo() = 0;
			};
		}
	}
}
