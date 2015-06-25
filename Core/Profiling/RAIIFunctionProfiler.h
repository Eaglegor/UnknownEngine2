#pragma once

#include <Profiling_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Profiling
		{
			class RAIIFunctionProfiler
			{
			public:
				PROFILING_EXPORT
				RAIIFunctionProfiler(const char* name);
				
				PROFILING_EXPORT
				~RAIIFunctionProfiler();
			};
		}
	}
}