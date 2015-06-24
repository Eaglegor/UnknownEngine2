#pragma once

#include <unordered_map>
#include <thread>

#include <Utils/Common/Singleton.h>

#include <Profiling_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Profiling
		{
			class IProfilerInstance;

			class ProfileManager : public Utils::Common::Singleton<ProfileManager>
			{
				public:
					PROFILING_EXPORT
					virtual ~ProfileManager(){}
					
					PROFILING_EXPORT
					IProfilerInstance* getProfilerInstance();
					
				private:
					std::unordered_map<std::thread::id, std::shared_ptr<IProfilerInstance> > profiler_instances;
			};
		}
	}
	
	namespace Utils
	{
		namespace Common
		{
#ifdef _MSC_VER
			#ifndef Profiling_EXPORTS
			extern template class PROFILING_EXPORT Singleton<Core::Profiling::ProfileManager>;
			#else
			template class PROFILING_EXPORT Singleton<Core::Profiling::ProfileManager>;
			#endif
#endif
		}
	}
}
