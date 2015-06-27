#include "PluginsManager.h"
#include "IPlugin.h"
#include <Core/OS/DLLUtils.h>

#include <Core/Profiling/ProfileMacros.h>

namespace UnknownEngine
{
	
	template<>
	Core::Plugins::PluginsManager* Utils::Common::Singleton<Core::Plugins::PluginsManager>::instance = nullptr;
	
	namespace Core
	{
		namespace Plugins
		{
			typedef IPlugin* (*CreatePluginInstanceFunc)(void);
			typedef void (*DestroyPluginInstanceFunc)(IPlugin*);
			
			bool PluginsManager::loadPlugin ( const char* filename )
			{
				PROFILE_FUNCTION();
				
				void* library_handle = OS::DLLUtils::loadLibrary(filename);
				if(library_handle == nullptr)
				{
					//[ERROR]
					return false;
				}
				CreatePluginInstanceFunc init_function = reinterpret_cast<CreatePluginInstanceFunc>(OS::DLLUtils::getFunctionAddress(library_handle, "createInstance"));
				if(init_function == nullptr)
				{
					//[ERROR]
					return false;
				}
				if(OS::DLLUtils::getFunctionAddress(library_handle, "destroyInstance") == nullptr)
				{
					//[ERROR]
					return false;
				}
				
				IPlugin* plugin = init_function();
				
				if(plugin == nullptr)
				{
					//[ERROR]
					return false;
				}
				
				LoadedPlugin loaded_plugin;
				loaded_plugin.plugin_instance = plugin;
				loaded_plugin.library_handle = library_handle;
				
				plugin->postLoad();

				plugins.emplace(plugin->getName(), loaded_plugin);
				
				return true;
			}

			bool PluginsManager::pluginIsLoaded ( const char* name ) const
			{
				PROFILE_FUNCTION();
				return plugins.find(name) != plugins.end();
			}

			bool PluginsManager::unloadAll()
			{
				PROFILE_FUNCTION();
				
				while(!plugins.empty())
				{
					bool success = unloadPlugin(plugins.begin()->second.plugin_instance->getName(), true);
					if(!success)
					{
						//[ERROR]
						return false;
					}
				}
				
				return true;
			}

			bool PluginsManager::unloadPlugin ( const char* name, bool cascade)
			{
				PROFILE_FUNCTION();
				
				auto main_iter = plugins.find(name);
				if(main_iter == plugins.end())
				{
					//[ERROR]
					return false;
				}
				while(!main_iter->second.dependent_plugins.empty())
				{
					if(!cascade)
					{
						//[ERROR]
						return false;
					}
					bool success = unloadPlugin((*main_iter->second.dependent_plugins.begin())->getName(), cascade);
					if(!success)
					{
						//[ERROR]
						return false;
					}
				}
				IPlugin* plugin = main_iter->second.plugin_instance;
				void* library_handle = main_iter->second.library_handle;
				
				plugin->preUnload();

				DestroyPluginInstanceFunc destroy_function = reinterpret_cast<DestroyPluginInstanceFunc>(OS::DLLUtils::getFunctionAddress(library_handle, "destroyInstance"));
				destroy_function(plugin);
				bool success = OS::DLLUtils::unloadLibrary(library_handle);
				return success;
			}
			
			void PluginsManager::addDependency ( IPlugin* main, IPlugin* dependent )
			{
				PROFILE_FUNCTION();
				
				auto main_iter = plugins.find(main->getName());
				auto dependent_iter = plugins.find(dependent->getName());
				if(main_iter == plugins.end() || dependent_iter == plugins.end())
				{
					//[ERROR]
					return;
				}
				main_iter->second.dependent_plugins.emplace(dependent);
			}

			version_t PluginsManager::getPluginVersion(const char* name)
			{
				auto iter = plugins.find(name);
				if (iter == plugins.end())
				{
					//[ERROR]
					return 0;
				}
				return iter->second.plugin_instance->getVersion();
			}

			IPlugin* PluginsManager::getPlugin(const char* name) const
			{
				auto iter = plugins.find(name);
				if (iter == plugins.end()) {
					//[ERROR]
					return nullptr;
				}
				return iter->second.plugin_instance;
			}
		}
	}
}