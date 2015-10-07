#pragma once

#include <Utils/Common/String.h>
#include "TypeSize.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			using Utils::Common::RawString;

			enum class ReflectableObjectType
			{
				MESSAGE,
				COMPONENT,
				SUBSYSTEM
			};

			class IMetaType
			{
				public:
					virtual ~IMetaType(){}

					virtual RawString getName() = 0;
					virtual TypeSize getSize() = 0;
					virtual ReflectableObjectType getObjectType() = 0;
			};
		}
	}
}
