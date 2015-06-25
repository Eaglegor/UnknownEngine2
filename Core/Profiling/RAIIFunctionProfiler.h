#pragma once

#include <Profiling_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Profiling
		{
			class PROFILING_EXPORT RAIIFunctionProfiler
			{
			public:
				
				RAIIFunctionProfiler(const char* name);
				~RAIIFunctionProfiler();
			};
		}
	}
}