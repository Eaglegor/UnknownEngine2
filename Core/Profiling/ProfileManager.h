#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Profiling
		{
			class IProfilerInstance;

			class ProfileManager
			{
				public:
					virtual ~ProfileManager(){}
					IProfilerInstance* getProfilerInstance();
			};
		}
	}
}
