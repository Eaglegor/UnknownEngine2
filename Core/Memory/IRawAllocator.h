#pragma once

#include <Memory_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Memory
		{
			class MEMORY_EXPORT IRawAllocator
			{
				public:
					virtual ~IRawAllocator(){}

					virtual void* allocateMemory(size_t amount) = 0;
					virtual void deallocateMemory(void* p) = 0;
			};
		}
	}
}
