#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class IPropertyTypeMetaInfo
			{
				public:
					virtual ~IPropertyTypeMetaInfo(){}
					virtual const char* getName() = 0;
			};
		}
	}
}
