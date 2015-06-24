#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class IPropertiesMap;
		}

		namespace Serialization
		{
			class Serializable
			{
				public:
					virtual ~Serializable(){}
					virtual Reflection::IPropertiesMap* getProperties() = 0;
			};
		}
	}
}
