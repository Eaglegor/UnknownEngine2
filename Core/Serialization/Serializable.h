#pragma once

#include <Core/Reflection/Reflectable.h>

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
			class Serializable : public Reflection::Reflectable
			{
			};
		}
	}
}
