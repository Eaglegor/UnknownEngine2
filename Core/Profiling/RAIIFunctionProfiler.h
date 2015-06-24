#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Profiling
		{
			class RAIIFunctionProfiler
			{
			public:
				RAIIFunctionProfiler(const char* name);
				~RAIIFunctionProfiler();
			};
		}
	}
}