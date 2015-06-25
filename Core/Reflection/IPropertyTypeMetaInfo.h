#pragma once

#include "ITypeMetaInfo.h"
#include <Reflection_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class REFLECTION_EXPORT IPropertyTypeMetaInfo : public ITypeMetaInfo
			{
				public:
					virtual ~IPropertyTypeMetaInfo(){}
					virtual const char* getName() = 0;
					virtual ITypeMetaInfo::Type getType(){return ITypeMetaInfo::Type::PROPERTY;}
			};
		}
	}
}
