#pragma once

#include <utility>
#include "IRawAllocator.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Memory
		{
			template<typename T>
			class TypedAllocator
			{
				public:
					typedef T* pointer;
					typedef size_t size_type;

					TypedAllocator():
					raw_allocator(nullptr)
					{}

					pointer allocate(size_type n)
					{
						raw_allocator->allocate(n*sizeof(T));
					}

					void deallocate(pointer p, size_type n)
					{
						raw_allocator->deallocate(n*sizeof(T));
					}

					template<typename U, typename... Args>
					void construct(U* p, Args&& ...args)
					{
						new ((void*)p) U (std::forward<Args>(args)...);
					}

					template<typename U>
					void destroy(U* p)
					{
						p->~U();
					}

				private:
					IRawAllocator* raw_allocator;
			};
		}
	}
}
