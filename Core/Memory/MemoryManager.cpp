#include "MemoryManager.h"
#include "New.h"
#include <Memory_export.h>

namespace UnknownEngine
{

	template<>
	MEMORY_EXPORT
	Core::Memory::MemoryManager* Utils::Common::Singleton<Core::Memory::MemoryManager>::instance = nullptr;

	namespace Core
	{
		namespace Memory
		{
			
		}
	}
}