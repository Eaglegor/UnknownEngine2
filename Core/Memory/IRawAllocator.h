#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Memory
		{
			class IRawAllocator
			{
				public:
					virtual ~IRawAllocator(){}

					virtual void* allocateMemory(size_t amount) = 0;
					virtual void deallocateMemory(void* p) = 0;
			};
		}
	}
}
