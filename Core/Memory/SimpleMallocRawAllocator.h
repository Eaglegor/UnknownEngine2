#pragma once

#include <cstddef>
#include "IRawAllocator.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Memory
		{
			class SimpleMallocRawAllocator : public IRawAllocator
			{
				public:
					virtual void* allocateMemory(std::size_t amount);
					virtual void deallocateMemory(void* p);
			};
		}
	}
}
