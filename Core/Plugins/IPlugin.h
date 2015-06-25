#pragma once

#include "PluginVersion.h"
#include <Plugins_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Plugins
		{
	
			class PLUGINS_EXPORT IPlugin
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