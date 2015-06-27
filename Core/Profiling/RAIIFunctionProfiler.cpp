#include "RAIIFunctionProfiler.h"
#include "IProfilerInstance.h"
#include "ProfileManager.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Profiling
		{
			RAIIFunctionProfiler::RAIIFunctionProfiler ( const char* name )
			{
				Core::Profiling::ProfileManager::getSingleton()->getProfilerInstance()->onFunctionStarted(name);
			}

			RAIIFunctionProfiler::~RAIIFunctionProfiler()
			{
				Core::Profiling::ProfileManager::getSingleton()->getProfilerInstance()->onFunctionEnded();
			}
		}
	}
}