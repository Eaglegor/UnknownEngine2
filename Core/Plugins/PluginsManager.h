#pragma once

#include <unordered_map>
#include <string>
#include <unordered_set>
#include <Utils/Common/Singleton.h>

#include <Plugins_export.h>


namespace UnknownEngine
{
	namespace Core
	{
		namespace Plugins
		{
			class IPlugin;
			
			class PluginsManager : public Utils::Common::Singleton<PluginsManager>
			{
			public:
				PLUGINS_EXPORT
				virtual ~PluginsManager(){}
				
				PLUGINS_EXPORT
				bool pluginIsLoaded(const char* name) const;
				
				PLUGINS_EXPORT
				bool loadPlugin(const char* filename);
				
				PLUGINS_EXPORT
				bool unloadPlugin(const char* name, bool cascade);
				
				PLUGINS_EXPORT
				bool unloadAll();
				
				PLUGINS_EXPORT
				void addDependency(IPlugin* main, IPlugin* dependent);
				
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
	
	namespace Utils
	{
		namespace Common
		{
#ifdef _MSC_VER
			#ifndef Plugins_EXPORTS
			extern template class PLUGINS_EXPORT Singleton<Core::Plugins::PluginsManager>;
			#else
			template class PLUGINS_EXPORT Singleton<Core::Plugins::PluginsManager>;
			#endif
#endif
		}
	}
	
}