#include <stdlib.h>
#include "SimpleMallocRawAllocator.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Memory
		{

			void *SimpleMallocRawAllocator::allocateMemory(size_t amount)
			{
				return malloc(amount);
			}

			void SimpleMallocRawAllocator::deallocateMemory(void *p)
			{
				free(p);
			}

		}
	}
}
