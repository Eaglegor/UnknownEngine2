#pragma once

#include <unordered_map>
#include <thread>
#include <memory>

#include <Utils/Common/Singleton.h>

#include <Profiling_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Profiling
		{
			class IProfilerInstance;

			class PROFILING_EXPORT ProfileManager : public Utils::Common::Singleton<ProfileManager>
			{
				public:
					
					virtual ~ProfileManager(){}
					
					IProfilerInstance* getProfilerInstance();
					
				private:
					std::unordered_map<std::thread::id, std::shared_ptr<IProfilerInstance> > profiler_instances;
			};
		}
	}
}
