#include "MemoryManager.h"
#include "New.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Memory
		{
			template<>
			MemoryManager* Utils::Common::Singleton<Core::Memory::MemoryManager>::instance = nullptr;
		}
	}
}