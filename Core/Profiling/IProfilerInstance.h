#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Profiling
		{
			class IProfilerInstance
			{
				public:
					virtual ~IProfilerInstance(){}
					virtual void startFunction(const char* name) = 0;
					virtual void checkPoint(const char* name) = 0;
					virtual void endFunction() = 0;
			};
			
			class StubProfilerInstance : public IProfilerInstance
			{
			public:
				virtual void checkPoint ( const char* name ){};
				virtual void endFunction(){};
				virtual void startFunction ( const char* name ){};
			};
		}
	}
}
