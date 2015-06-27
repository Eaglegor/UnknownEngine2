#include <Core/Plugins/IPlugin.h>
#include <Core/Plugins/PluginsManager.h>
#include <iostream>
#include <SamplePlugin_export.h>

using namespace UnknownEngine::Core::Plugins;

namespace UnknownEngine
{
	namespace Plugins
	{
		namespace SamplePlugin
		{
			class SamplePlugin : public IPlugin
			{
			public:
				virtual void postLoad()
				{
					std::cout << "Post load called" << std::endl;
				}

				virtual void preUnload()
				{
					std::cout << "Pre unload called" << std::endl;
				}

				virtual const char* getName() const
				{
					return "SamplePlugin";
				}

				virtual version_t getVersion() const
				{
					return 1;
				}
			};

		}
	}
}

extern "C" SAMPLEPLUGIN_EXPORT
IPlugin* createInstance()
{
	return new UnknownEngine::Plugins::SamplePlugin::SamplePlugin();
}

extern "C" SAMPLEPLUGIN_EXPORT
void destroyInstance(IPlugin* plugin)
{
	delete plugin;
}