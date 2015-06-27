#pragma once

#include "IRawAllocator.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Memory
		{
			template<typename T, std::size_t Alignment>
			class AlignedRawAllocator : public IRawAllocator
			{
			public:
				virtual void* allocateMemory ( std::size_t amount );
				virtual void deallocateMemory ( void* p );
			};
		}
	}
}