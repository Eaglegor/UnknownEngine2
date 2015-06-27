#pragma once

#include <cstddef>
#include <Profiling_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Profiling
		{
			
			class PROFILING_EXPORT IProfilerInstance
			{
				public:
					virtual ~IProfilerInstance(){}
					virtual void onFunctionStarted(const char* name) = 0;
					virtual void onCheckpoint(const char* name) = 0;
					virtual void onFunctionEnded() = 0;
					virtual void onMemoryAllocated(std::size_t size) = 0;
					virtual void onMemoryDeallocated(std::size_t size) = 0;
			};
			
			class StubProfilerInstance : public IProfilerInstance
			{
			public:
				virtual void onFunctionStarted ( const char* name ){}
				virtual void onCheckpoint ( const char* name ){}
				virtual void onFunctionEnded(){}
				virtual void onMemoryAllocated ( std::size_t size ){}
				virtual void onMemoryDeallocated ( std::size_t size ){}
			};
		}
	}
}
