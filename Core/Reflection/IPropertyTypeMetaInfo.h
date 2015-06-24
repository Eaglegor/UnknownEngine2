#pragma once

#include "ITypeMetaInfo.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class IPropertyTypeMetaInfo : public IMetaInfo
			{
				public:
					virtual ~IPropertyTypeMetaInfo(){}
					virtual const char* getName() = 0;
					virtual ITypeMetaInfo::Type getType(){return IMetaInfo::Type::PROPERTY;}
			};
		}
	}
}
