#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Plugins
		{
			typedef size_t version_t;
			
			class IPlugin
			{
			public:
				virtual ~IPlugin(){}
				
				virtual void postLoad() = 0;
				virtual void preUnload() = 0;
				
				virtual const char* getName() const = 0;
				virtual version_t getVersion() const = 0;
			};
		}
	}
}