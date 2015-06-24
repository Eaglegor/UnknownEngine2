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
					virtual ITypeMetaInfo* getMetaInformation(const char* type_name);

					template<typename T>
					virtual ITypeMetaInfo* registerType<T>(const char* type_name)
					{
						// Register types
						return nullptr;
					}
			};
		}
	}
}
