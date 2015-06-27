#pragma once

#include <cstddef>
#include <cstdlib>
#include "Policies.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Memory
		{
			inline void* Malloc(std::size_t size, AllocationPolicy allocation_policy, std::size_t alignment)
			{
				return ::malloc(size);
			}

			inline void* Realloc(void* ptr, std::size_t size)
			{
				return ::realloc(ptr, size);
			}
			
			inline void Free(void* ptr)
			{
				::free(ptr);
			}
		}
	}
}


void* operator new(std::size_t size)
{
	return UnknownEngine::Core::Memory::Malloc(size, UnknownEngine::Core::Memory::AllocationPolicy::GENERIC, 16);
}

void* operator new[](std::size_t size)
{
	return UnknownEngine::Core::Memory::Malloc(size, UnknownEngine::Core::Memory::AllocationPolicy::GENERIC, 16);
}

void operator delete(void* pointer)
{
	UnknownEngine::Core::Memory::Free(pointer);
}

void operator delete[](void* pointer)
{
	UnknownEngine::Core::Memory::Free(pointer);
}
