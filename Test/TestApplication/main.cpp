#include <Core/Plugins/PluginsManager.h>
#include <Core/Profiling/ProfileManager.h>

#include <iostream>

int main(int argc, char** argv)
{
	using namespace UnknownEngine::Core::Plugins;
	using namespace UnknownEngine::Core::Profiling;

	ProfileManager::createInstance();

	PluginsManager* mgr = PluginsManager::createInstance();

	mgr->loadPlugin("plugins/SamplePlugin.dll");

	std::cout << "Sample plugin version: " << mgr->getPluginVersion("SamplePlugin") << std::endl;

	mgr->unloadPlugin("SamplePlugin", false);

	return 0;
}