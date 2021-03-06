#include <memory>
#include "ProfileManager.h"
#include "IProfilerInstance.h"
#include <Profiling_export.h>

namespace UnknownEngine
{
	template<>
	#ifndef _MSC_VER 
	PROFILING_EXPORT
	#endif
	Core::Profiling::ProfileManager* Utils::Common::Singleton<Core::Profiling::ProfileManager>::instance = nullptr;

	namespace Core
	{
		namespace Profiling
		{
			IProfilerInstance* ProfileManager::getProfilerInstance()
			{
				std::thread::id thread_id = std::this_thread::get_id();
				auto iter = profiler_instances.find(thread_id);
				if(iter == profiler_instances.end())
				{
					iter = profiler_instances.emplace(thread_id, std::make_shared<StubProfilerInstance>()).first;
				}
				return iter->second.get();
			}
		}
	}
}