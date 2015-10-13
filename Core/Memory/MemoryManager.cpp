#include "MemoryManager.h"
#include "New.h"

namespace UnknownEngine
{
	namespace Utils
	{
		namespace Common
		{
			template<>
			Core::Memory::MemoryManager* Singleton<Core::Memory::MemoryManager>::instance = nullptr;
		}
	}

	namespace Core
	{
		namespace Memory
		{
			
		}
	}
}