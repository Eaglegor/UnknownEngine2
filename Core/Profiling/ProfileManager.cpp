#include "stdafx.h"

#include "ProfileManager.h"
#include "IProfilerInstance.h"

namespace UnknownEngine
{
	namespace Utils
	{
		namespace Common
		{
			template<>
			Core::Profiling::ProfileManager* Singleton<Core::Profiling::ProfileManager>::instance = nullptr;
		}
	}
	
	namespace Core
	{
		namespace Profiling
		{
			IProfilerInstance* ProfileManager::getProfilerInstance()
			{
				auto iter = profiler_instances.find(std::this_thread::get_id());
				if(iter == profiler_instances.end())
				{
					iter = profiler_instances.emplace(std::this_thread::get_id(), std::make_shared<StubProfilerInstance>()).first;
				}
				return iter->second.get();
			}
		}
	}
}