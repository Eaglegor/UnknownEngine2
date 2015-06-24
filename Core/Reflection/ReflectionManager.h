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
					ITypeMetaInfo* getMetaInformation(const char* type_name);

					template<typename T>
					ITypeMetaInfo* registerType(const char* type_name)
					{
						// Register types
						return nullptr;
					}
			};
		}
	}
}
