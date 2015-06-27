#pragma once

#include <Utils/Common/Singleton.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Memory
		{
			class MemoryManager : public Utils::Common::Singleton<MemoryManager>
			{
			public:
				virtual ~MemoryManager(){}
				
				virtual void* allocate(std::size_t size);
				virtual void deallocate(void* p);
				
			private:
				
			};
		}
	}
}