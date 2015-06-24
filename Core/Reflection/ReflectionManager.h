#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Reflection
		{
			class ITypeMetaInfo;

			class ReflectionManager
			{
				public:
					virtual ~ReflectionManager(){}
					virtual ITypeMetaInfo* getMetaInformation(const char* type_name) = 0;
					virtual registerType(const char* type_name, ITypeMetaInfo* meta_info) = 0;
			};
		}
	}
}
