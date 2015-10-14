#include "MemoryManager.h"
#include "New.h"
#include <Memory_export.h>

namespace UnknownEngine
{

	template<>
	#ifndef _MSC_VER 
	MEMORY_EXPORT
	#endif
	Core::Memory::MemoryManager* Utils::Common::Singleton<Core::Memory::MemoryManager>::instance = nullptr;

	namespace Core
	{
		namespace Memory
		{
			
		}
	}
}