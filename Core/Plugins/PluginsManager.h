#pragma once

#include <unordered_map>
#include <string>
#include <unordered_set>
#include <Utils/Common/Singleton.h>
#include "PluginVersion.h"

#include <Plugins_export.h>


namespace UnknownEngine
{
	namespace Core
	{
		namespace Plugins
		{
			class IPlugin;
			
			class PLUGINS_EXPORT PluginsManager : public Utils::Common::Singleton<PluginsManager>
			{
			public:
				
				virtual ~PluginsManager(){}
				
				bool pluginIsLoaded(const char* name) const;
				bool loadPlugin(const char* filename);
				bool unloadPlugin(const char* name, bool cascade);
				bool unloadAll();
				void addDependency(IPlugin* main, IPlugin* dependent);

				version_t getPluginVersion(const char* name);
				
			private:
				struct LoadedPlugin
				{
					void* library_handle;
					IPlugin* plugin_instance;
					std::unordered_set<IPlugin*> dependent_plugins;
				};
				
				std::unordered_map<std::string, LoadedPlugin> plugins;
			};
		}
	}
}