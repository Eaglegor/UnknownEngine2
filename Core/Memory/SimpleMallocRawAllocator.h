#pragma once

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
					virtual void* allocateMemory(size_t amount);
					virtual void deallocateMemory(void* p);
			};
		}
	}
}
