#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class ITypeMetaInfo
			{
				public:
					enum class Type
					{
						MESSAGE,
						COMPONENT,
						SUBSYSTEM,
						PROPERTY
					};

					virtual ~ITypeMetaInfo(){}
					virtual Type getMetaInfoType() = 0;
			};
		}
	}
}
